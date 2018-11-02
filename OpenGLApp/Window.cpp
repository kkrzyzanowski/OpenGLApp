#include "Window.h"
#include "Renderer.h"
#include "ShaderManager.h"
#include "ShapesBuilder.h"
#include "Camera.h"
#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtc\type_ptr.hpp"
#include "Cube.h"
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
	// glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	
	 GLenum err = glewInit();
	 if (GLEW_OK != err)
	 {
		 return -1;
	 }
	 glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);


	 Camera* cam = new Camera();
	 glm::vec3 camProps[3] = {
		 glm::vec3(0.0f, 0.0f, 3.0f),
		 glm::vec3(0.0f, 0.0f, -.1f),
		 glm::vec3(0.0f, 1.0f, 0.0f)
	 };
	 cam->CreateView(camProps, 5.0f, window);
	 ShapesBuilder shapesBuilder;
	 shapes.push_back(shapesBuilder.ObjectState(CamView::DYNAMIC)
		 .SourceType(SourceShapeType::LIGHT)
		 .CreateShape(Shapes::SPEHERE));
	 
	 shapes.push_back(shapesBuilder.ObjectState(CamView::STATIC)
		 .SourceType(SourceShapeType::DIFFUSE)
		 .CreateShape(Shapes::RECTANGLE));
	 for each (Shape* shape in shapes)
	 {
		 shape->InitializeShapeView(cam->GetView());
		 shape->SetEyeCamPos(cam->GetCamPos());
		 shape->GenerateShaders();
		 shape->TurnOffShapeElements();
	}
	 shapes[1]->SetOutsideLight(shapes[0]->GetInsideLight());
	 renderer = new Renderer();
	glEnable(GL_DEPTH_TEST);
	 /* Loop until the user closes the window */
	 while (!glfwWindowShouldClose(window) && glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS)
	 {
		
		 /* Render here */
		 renderer->Clear();
	
		 cam->Update();
		int count = 0;
		 for each (auto shape in shapes)
		 {
			 shape->InitializeShapeView(cam->GetView());
			 shape->SetEyeCamPos(cam->GetCamPos());
			 shape->SetOutsideLight(shapes[0]->GetInsideLight());
			 shape->Update();
			 renderer->Draw(shape->GetIndexBuffer()->GetCount());
			 shape->TurnOffShapeElements();
		 }
		 /* Swap front and back buffers */
		 glfwSwapBuffers(window);

		 /* Poll for and process events */
		 glfwPollEvents();
	 }
	

//	 sm.UnBind();
	 glfwTerminate();
	
	 return 0;
}
Window::~Window()
{
	delete renderer;
	delete this;
}

