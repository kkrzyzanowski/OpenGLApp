
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


	/* Set cameras */
	//CameraManager camManager;

	//Camera* cam = new Camera();
	//glm::vec3 camProps[3] = {
	//	glm::vec3(0.0f, 0.0f, 15.0f), // position
	//	glm::vec3(0.0f, 0.0f, -1.0f), // looking
	//	glm::vec3(0.0f, 1.0f, 0.0f) // up direction
	//};

	//cam->CreateView(camProps, 5.0f, window);
	//camManager.AddCamera(cam);
	//camManager.SetActiveCamera(cam);

	//glScalef(1.0f, 1.0f, 1.0f);

	//Controls* control = new Controls(window);
	///* Creation all objects in scene */
	//ShapesBuilder shapesBuilder;

	//ShapeManager::shapes.push_back(shapesBuilder.ObjectState(CamView::DYNAMIC)
	//	.SourceType(SourceShapeType::LIGHT)
	//	.CreateShape(Shapes::SPEHERE));

	//ShapeManager::shapes.push_back(shapesBuilder.ObjectState(CamView::STATIC)
	//	.SourceType(SourceShapeType::DIFFUSE)
	//	.CreateShape(Shapes::RECTANGLE));

	//ShapeManager::shapes.push_back(shapesBuilder.ObjectState(CamView::DYNAMIC)
	//	.SourceType(SourceShapeType::DIFFUSE)
	//	.CreateShape(Shapes::CUBE));

	//ShapeManager::shapes.push_back(shapesBuilder.ObjectState(CamView::DYNAMIC)
	//	.SourceType(SourceShapeType::LIGHT)
	//	.PathModel("Models\\Hammer.obj")
	//	.CreateShape(Shapes::CUSTOM));

	//ShapeManager::shapes.push_back(shapesBuilder.ObjectState(CamView::DYNAMIC)
	//	.SourceType(SourceShapeType::DIFFUSE)
	//	.CreateShape(Shapes::CUBEBOX));

	//ShapeManager::shapes.push_back(shapesBuilder.ObjectState(CamView::MOVABLE)
	//	.SourceType(SourceShapeType::DIFFUSE)
	//	.CreateShape(Shapes::LINE));


	//for each (Shape* shape in   ShapeManager::shapes)
	//{
	//	shape->InitializeShapeView(cam->GetView());
	//	shape->ApplyProjectionMatrix(cam->GetProjection());
	//	shape->SetEyeCamPos(cam->GetCamPos());
	//	shape->GenerateShaders();
	//	shape->TurnOffShapeElements();
	//	if (shape->GetState() == CamView::MOVABLE)
	//		cam->movableShapes.push_back(shape);
	//}
	//ShapeManager::shapes[1]->SetOutsideLight(ShapeManager::shapes[0]->GetInsideLight());

	//FrameBuffer* frameBuffer = new FrameBuffer();
	//frameBuffer->Bind();
	//frameBuffer->GenerateTextureColorBuffer();
	//frameBuffer->GenerateRenderBuffer();
	//bool isFrameBufferLoaded = frameBuffer->CheckFrameBuffer();
	//frameBuffer->InitializePostProcessingShaders();
	//frameBuffer->UnBind();

	//renderer = new Renderer();
	//rayDrawer = new RayDrawer();

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
		//frameBuffer->Bind();
		glEnable(GL_DEPTH_TEST);
		//renderer->Clear();
		glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
		//glStencilFunc(GL_ALWAYS, 1, 0xFF);
		//glStencilMask(0xFF);
		//cam->Update();
		int count = 0;

		//for each (auto shape in   ShapeManager::shapes)
		//{
		//	shape->InitializeShapeView(cam->GetView());
		//	shape->SetEyeCamPos(cam->GetCamPos());
		//	shape->TurnOffShapeElements();
		//	shape->SetOutsideLight(ShapeManager::shapes[0]->GetInsideLight());
		//	shape->Update();
		//	if (shape->GetSourceShapeType() != SourceShapeType::PRIMITIVE)
		//		renderer->Draw(shape->GetIndexBuffer()->GetCount());
		//	else
		//	{
		//		/*if (dynamic_cast<Primitive*>(shape) != nullptr)
		//		{
		//			Primitive* p = dynamic_cast<Primitive*>(shape);
		//			delete p;
		//		}*/
		//	}
		//}
		//if (cam->mouseRayCast != nullptr)
		//{
		//	//glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
		//	//glClearColor(1.0f, 0.2f, 0.3f, 1.0f);
		//	//glClear(GL_COLOR_BUFFER_BIT);
		///*	glm::vec3 tempvec = glm::vec3(
		//		cam->mouseRayCast->GetWorldRay().x,
		//		cam->mouseRayCast->GetWorldRay().y,
		//		cam->mouseRayCast->GetWorldRay().z + 15.0f);
		//	rayDrawer->DrawRay(tempvec, tempvec, -1000.0f, renderer);*/

		//}
		//frameBuffer->TurnOffFrameBufferElements();
		//frameBuffer->UnBind();
		//glDisable(GL_DEPTH_TEST);
		////glClear(GL_COLOR_BUFFER_BIT);
		//frameBuffer->TurnOnFrameBufferElements();
		//frameBuffer->BindTexture();
		//renderer->Draw(frameBuffer->GetIndexBuffer()->GetCount());
		 /* Swap front and back buffers */
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

