
#include <GL\glew.h>
#include <vector>
#include <typeinfo>
#include "GameWindow.h"

//#include "Window.h"
//#include "Renderer.h"
//#include "ShapesBuilder.h"
//#include "ShaderManager.h"
//#include "Camera.h"
//#include "FrameBuffer.h"
//#include "Config.h"
//#include "glm\glm.hpp"
//#include "glm\gtc\matrix_transform.hpp"
//#include "glm\gtc\type_ptr.hpp"
//#include "SkyBoxCube.h"
//#include "Controls.h"
//#include "ShapeManager.h"
//#include "RayDrawer.h"
//#include "Primitive.h"

//bool RayCastDetection(glm::vec3 rayOrigin, glm::vec3 rayDirection, glm::vec3 normal, glm::vec3 shapePoint, float &distance);
//
//RayDrawer* rayDrawer;

OpenGLGameWindow::OpenGLGameWindow()
{
	CreateWindow();
}

int OpenGLGameWindow::CreateWindow()
{
	// Creation window
	if (!glfwInit())
		return -1;

	glfwWindowHint(GLFW_SAMPLES, 4);
	GLFWwindow* window;
	window = glfwCreateWindow(800, 600, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	// OpenGL params

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	// glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		return -1;
	}
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);


	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDepthFunc(GL_LESS);
	glEnable(GL_STENCIL_TEST);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

	float distance = 1000.0f;

	GLfloat color[] = {
		255, 0, 0
	};
	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window) && glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS)
	{

		/* Render here */

		glEnable(GL_DEPTH_TEST);

		glClearColor(0.1f, 0.2f, 0.3f, 1.0f);

		int count = 0;
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}


	//	 sm.UnBind();
	glfwTerminate();

	return 0;
}
OpenGLGameWindow::~OpenGLGameWindow()
{
	//delete renderer;
	delete this;
}

