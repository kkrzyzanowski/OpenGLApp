#include <vector>
#include <typeinfo>

#include "Window.h"
#include "Renderer.h"
#include "ShapesBuilder.h"
#include "ShaderManager.h"
#include "Camera.h"
#include "FrameBuffer.h"
#include "Config.h"
#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtc\type_ptr.hpp"
#include "SkyBoxCube.h"
#include "Controls.h"
#include "ShapeManager.h"
#include "RayDrawer.h"
#include "Primitive.h"
#include "Collision.h"
#include "CustomProperties.h"
#include "Terrain.h"
#include "StencilOutline.h"

bool RayCastDetection(glm::vec3 rayOrigin, glm::vec3 rayDirection, glm::vec3 normal, glm::vec3 shapePoint, float &distance);
void OutlineObject();
void DisableOutline();
RayDrawer* rayDrawer;

GameWindow::GameWindow()
{
	CreateWindow();
}

 int GameWindow::CreateWindow()
{
	 // Creation window
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
	 CameraManager camManager;

	 Camera* cam = new Camera ();
	 glm::vec3 camProps[3] = {
		 glm::vec3(0.0f, 0.0f, 0.0f), // position
		 glm::vec3(0.0f, 0.0f, -1.0f), // looking
		 glm::vec3(0.0f, 1.0f, 0.0f) // up direction
	 };
	 
	 cam->CreateView(camProps, 5.0f, window);
	 camManager.AddCamera(cam);
	 camManager.SetActiveCamera(cam);

	 
	 Controls* control = new Controls(window);
	 /* Creation all objects in scene */
	 ShapesBuilder shapesBuilder;
	 
	 //ShapeManager::shapes.emplace_back(shapesBuilder.ObjectState(CamView::DYNAMIC)
		// .SourceType(SourceShapeType::LIGHT)
		// .CreateShape(ShapeType::SPEHERE));

	 ShapeManager::shapes.emplace_back(shapesBuilder.ObjectState(CamView::DYNAMIC)
		 .SourceType(SourceShapeType::DIFFUSE)
		 .CreateShape(ShapeType::RECTANGLE));

	 ShapeManager::shapes.emplace_back(shapesBuilder.ObjectState(CamView::DYNAMIC)
		 .SourceType(SourceShapeType::DIFFUSE)
		 .CreateShape(ShapeType::CUBE));

	 //ShapeManager::shapes.push_back(shapesBuilder.ObjectState(CamView::DYNAMIC)
		// .SourceType(SourceShapeType::LIGHT)
		// .PathModel("Models\\Hammer.obj")
		// .CreateShape(ShapeType::CUSTOM));

	 ShapeManager::shapes.push_back(shapesBuilder.ObjectState(CamView::DYNAMIC)
		 .SourceType(SourceShapeType::DIFFUSE)
		 .CreateShape(ShapeType::SKYBOX));

	 //ShapeManager::shapes.push_back(shapesBuilder.ObjectState(CamView::MOVABLE)
		// .SourceType(SourceShapeType::DIFFUSE)
		// .CreateShape(ShapeType::LINE));

	 //TerrainProperties tp = { -4.0f, 1.0f, 12, 12, glm::vec3(0.0f, -4.0f, 0.0f) };
	 //ShapeManager::shapes.push_back(shapesBuilder.ObjectState(CamView::DYNAMIC)
		// .SourceType(SourceShapeType::DIFFUSE)
		// .CustomProperties(tp)
		// .CreateShape(ShapeType::TERRAIN));

	 for each (auto& shape in  ShapeManager::shapes)
	 {
		 shape->InitializeShapeView(cam->GetView());
		 shape->ApplyProjectionMatrix(cam->GetProjection());
		 shape->SetEyeCamPos(cam->GetCamPos());
		 shape->GenerateShaders();
		 shape->TurnOffShapeElements();
		 shape->InitializePickedShape();
		 if (shape->GetCreationState() == CamView::MOVABLE)
			 cam->movableShapes.push_back(shape);
	}
	//ShapeManager::shapes[1]->SetOutsideLight(ShapeManager::shapes[0]->GetInsideLight());

	FrameBuffer* frameBuffer = new FrameBuffer();
	RenderBuffer* renderBuffer = new RenderBuffer();
	
	frameBuffer->Bind();
	frameBuffer->GenerateTexture();
	
	frameBuffer->InitializePostProcessingShaders();
	renderBuffer->Bind();
	renderBuffer->GenerateRenderBuffer();
	renderBuffer->GenerateFrameRenderBuffer();
	if (!frameBuffer->CheckFrameBuffer())
		return -1;

	frameBuffer->UnBind();


	//Collision initialization
	Collision* collision = new Collision();
	collision->objects = ShapeManager::shapes;

	renderer = new Renderer();
	rayDrawer = new RayDrawer();
	
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
		//glDepthFunc(GL_LEQUAL);
		glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
		renderer->Clear();
		//glStencilFunc(GL_ALWAYS, 1, 0xFF);
		//glStencilMask(0xFF);
		cam->Update();
		int count = 0;
		for each (auto& shape in  ShapeManager::shapes)
		{
			if (shape->Selected && shape->GetType() != ShapeType::SKYBOX)
			{
				OutlineObject();
				shape->UpdatePickedShape();
			}
			else 
			{
				//DisableOutline();
			}
			shape->InitializeShapeView(cam->GetView());
			shape->SetEyeCamPos(cam->GetCamPos()); 
			shape->SetOutsideLight(ShapeManager::shapes[0]->GetInsideLight());
			shape->Update();
			if (shape->GetSourceShapeType() != SourceShapeType::PRIMITIVE)
			{
				auto terr = dynamic_cast<Terrain*>(shape.get());
				if(terr == nullptr)
					renderer->Draw(shape->GetIndexBuffer()->GetCount(), GL_TRIANGLES);
				else
					renderer->Draw(shape->GetIndexBuffer()->GetCount(), GL_TRIANGLE_FAN);

			}
			shape->TurnOffShapeElements();
			//Check collision - for now on main loop
			collision->CheckCollision();

				/*if (dynamic_cast<Primitive*>(shape) != nullptr)
				{
					Primitive* p = dynamic_cast<Primitive*>(shape);
					delete p;
				}*/
			
		}
		
		// Draw ray
		if(cam->mouseRayCast != nullptr)
		{ 
			//glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
			//glClearColor(1.0f, 0.2f, 0.3f, 1.0f);
			//glClear(GL_COLOR_BUFFER_BIT);
			glm::vec3 tempvec = glm::vec3(
				cam->mouseRayCast->GetWorldRayDirection().x,
				cam->mouseRayCast->GetWorldRayDirection().y,
				cam->mouseRayCast->GetWorldRayDirection().z + 15.0f);
			rayDrawer->DrawRay(tempvec, tempvec, 1000.0f, renderer);
			
		}

		//frameBuffer->TurnOffFrameBufferElements();
		////Post-procesing
		//frameBuffer->UnBind();
		//glDisable(GL_DEPTH_TEST);

		//glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		//glClear(GL_COLOR_BUFFER_BIT);

		//frameBuffer->TurnOnFrameBufferElements();
		//frameBuffer->GetFramebufferTexture()->Bind();
		//renderer->Draw(frameBuffer->GetIndexBuffer()->GetCount());

		/* Swap front and back buffers */
		 glfwSwapBuffers(window);

		 /* Poll for and process events */
		 glfwPollEvents();
	 }
	
	 glfwTerminate();
	
	 return 0;
}
GameWindow::~GameWindow()
{
	delete renderer;
	delete this;
}

void OutlineObject()
{
	glEnable(GL_STENCIL_TEST);
	glDisable(GL_DEPTH_TEST);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
	glStencilFunc(GL_ALWAYS, 1, 0xFF);
	glStencilMask(0xFF);
}

void DisableOutline()
{
	glStencilFunc(GL_NOTEQUAL, 1, 0x00);
	glStencilMask(0x00);
	glEnable(GL_DEPTH_TEST);
}
