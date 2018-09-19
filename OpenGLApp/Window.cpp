#include "Window.h"
#include "Renderer.h"
#include "ShaderManager.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "Camera.h"
#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtc\type_ptr.hpp"
#include <vector>

static const unsigned int SCREEN_WIDTH = 1280;
static const unsigned int SCREEN_HEIGHT= 720;

Window::Window()
{
	CreateWindow();
}

 int Window::CreateWindow()
{
	 if (!glfwInit())
		 return -1;

	 glfwWindowHint(GLFW_SAMPLES, 4);
	 GLFWwindow* window;
	 window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Hello World", NULL, NULL);
	 if (!window)
	 {
		 glfwTerminate();
		 return -1;
	 }
	 glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	 glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	 glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	 /* Make the window's context current */
	 glfwMakeContextCurrent(window);
	 glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	
	 GLenum err = glewInit();
	 if (GLEW_OK != err)
	 {
		 return -1;
	 }
	 glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);


	 shape = new Shape(TRIANGLE);
	 renderer = new Renderer();
	 Shader vertexShader("Shaders\\VertexShader.vert");
	 Shader fragmentShader("Shaders\\FragmentShader.frag");
	
	 Camera* cam = new Camera();
	 glm::vec3 camProps[3] = {
		 glm::vec3(0.0f, 0.0f, 3.0f),
		 glm::vec3(0.0f, 0.0f, -.1f),
		 glm::vec3(0.0f, 1.0f, 0.0f)
	 };
	 cam->CreateView(camProps, 5.0f, window);
	 std::vector<Shader> shaders;
	 shaders.push_back(vertexShader);
	 shaders.push_back(fragmentShader);
	 ShaderManager sm;
	sm.AddShadersToProgram(shaders);
	sm.Bind();
	glm::mat4 trans = glm::mat4(1.0f);
	//trans = glm::translate(trans, glm::vec3(0.0, 0.0, -0.4));
	//trans = glm::rotate(trans, glm::radians(10.0f), glm::vec3(0.0, 0.0, 1.0));
	glm::mat4 view = glm::mat4(1.0f);
	view = glm::translate(view, glm::vec3(0.0, 0.0, 0.5));
	glm::mat4 proj = glm::perspective(glm::radians(108.0f), 16.0f / 9.0f, 0.01f, 100.0f);
	glm::mat4 mvp = proj  * view * trans;
	fragmentShader.SetUniform4f("u_color", 0.9f, 0.4f, 0.6f, 0.8f, sm.GetProgram());
	 shape->GetTexture()->Bind();
	//texture.Bind();
	 vertexShader.SetUniformMat4f("u_MVP", mvp, sm.GetProgram());
	fragmentShader.SetUniform1i("u_texture", 0, sm.GetProgram());
	shape->GetVertexArray()->UnBind();
	shape->GetVertexBuffer()->UnBind();
	shape->GetIndexBuffer()->UnBind();
	sm.UnBind();
	glEnable(GL_DEPTH_TEST);
	 /* Loop until the user closes the window */
	 while (!glfwWindowShouldClose(window) && glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS)
	 {
		 /* Render here */
		 renderer->Clear();
		 sm.Bind();
		 trans = glm::mat4(1.0f);
		 trans = glm::rotate(trans, (float)glfwGetTime() * glm::radians(10.0f), glm::vec3(0.5f, 1.0f, 0.0f));
		 glm::mat4 mvp = proj * view;
		 vertexShader.SetUniformMat4f("u_MVP", mvp, sm.GetProgram());
		 auto camView = cam->Update();
		 vertexShader.SetUniformMat4f("u_camView", camView, sm.GetProgram());
		 sm.UnBind();
		// glDrawArrays(GL_TRIANGLES, 0, 4);
		 renderer->Draw(*shape->GetVertexArray(), *shape->GetIndexBuffer(), sm);

		 

		 /* Swap front and back buffers */
		 glfwSwapBuffers(window);

		 /* Poll for and process events */
		 glfwPollEvents();
	 }
	

	 sm.UnBind();
	 glfwTerminate();
	
	 return 0;
}
Window::~Window()
{
	delete shape;
	delete renderer;
	delete this;
}

