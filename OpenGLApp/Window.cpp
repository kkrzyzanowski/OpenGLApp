#include "Window.h"
#include "Renderer.h"
#include "ShaderManager.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include <vector>
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
	 window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
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
	 GLenum err = glewInit();
	 if (GLEW_OK != err)
	 {
		 return -1;
	 }
	 glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);


	 shape = new Shape(TRIANGLE);
	 Shader vertexShader("VertexShader.vert");
	 Shader fragmentShader("FragmentShader.frag");
	 std::vector<Shader> shaders;
	 shaders.push_back(vertexShader);
	 shaders.push_back(fragmentShader);
	 ShaderManager sm;
	sm.AddShadersToProgram(shaders);
	sm.Bind();
	
	shape->GetVertexArray()->UnBind();
	shape->GetVertexBuffer()->UnBind();
	shape->GetIndexBuffer()->UnBind();
	sm.UnBind();
		
		/* GLCall(glBindVertexArray(0));
		 GLCall(glUseProgram(0));
		 GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
		 GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));*/
	 /* Loop until the user closes the window */
	 while (!glfwWindowShouldClose(window) && glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS)
	 {
		 /* Render here */
		 GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT));
		// glDrawArrays(GL_TRIANGLES, 0, 4);
		 sm.Bind();
			shape->GetVertexArray()->Bind();
		 shape->GetIndexBuffer()->Bind();
		 GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));
		

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
	delete this;
}
