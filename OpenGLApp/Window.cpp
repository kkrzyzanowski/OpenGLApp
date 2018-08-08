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
	 renderer = new Renderer();
	 Shader vertexShader("Shaders\\VertexShader.vert");
	 Shader fragmentShader("Shaders\\FragmentShader.frag");
	 std::vector<Shader> shaders;
	 shaders.push_back(vertexShader);
	 shaders.push_back(fragmentShader);
	 ShaderManager sm;
	sm.AddShadersToProgram(shaders);
	sm.Bind();
	fragmentShader.SetUniform4f("u_color", 0.9f, 0.4f, 0.6f, 0.8f, sm.GetProgram());
	 shape->GetTexture()->Bind();
	//texture.Bind();
	fragmentShader.SetUniform1i("u_texture", 0, sm.GetProgram());
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
		 renderer->Clear();
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
