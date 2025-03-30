#include <vector>
#include <typeinfo>

#include "OpenGLGameWindow.h"
#include "Managers/FrameBufferManager.h"


// to-do do textures for framebuffer (maybe class or something like that) to prepare connection beetween framebuffers
// rewrite activate and deactivate binding textures with slots, set function colorattachment

void TurnOnStencilBufferMask();
void TurnOffStencilBufferMask();
void TurnOnNormalMask();

RayDrawer* rayDrawer;

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

	std::shared_ptr<Camera> cam = std::make_shared<Camera>();
	glm::vec3 camProps[3] = {
		glm::vec3(0.0f, 0.0f, 0.0f), // position
		glm::vec3(0.0f, 0.0f, -1.0f), // looking
		glm::vec3(0.0f, 1.0f, 0.0f) // up direction
	};

	cam->CreateView(camProps, 5.0f, window);
	camManager.AddCamera(cam.get());
	camManager.SetActiveCamera(cam.get());



	Controls* control = new Controls(window);
	/* Creation all objects in scene */
	std::unique_ptr<ShapesBuilder> shapesBuilder = std::make_unique<ShapesBuilder>();

	ShapeManager::shapes.emplace_back(shapesBuilder->ObjectState(CamView::DYNAMIC)
		.SourceType(SourceShapeType::SHAPE)
		.Texture(TEMP_TEXTURE_DIFFUSE)
		.Texture(TEMP_TEXTURE_SPECULAR)
		.Shader(DIFFUSE_VERT_PATH)
		.Shader(DIFFUSE_FRAG_PATH)
		.Shadow(true)
		.Position(glm::vec3(0.6f, -.9f, -3.0f))
		.Create(ShapeType::CUBE));

	ShapeManager::shapes.emplace_back(shapesBuilder->ObjectState(CamView::DYNAMIC)
		.SourceType(SourceShapeType::SHAPE)
		.Texture(TEMP_TEXTURE_DIFFUSE)
		.Texture(TEMP_TEXTURE_SPECULAR)
		.Shader(GBUFFER_VERT_PATH)
		.Shader(GBUFFER_FRAG_PATH)
		.SetShading(Shading::DEFFERED_SHADING)
		.Position(glm::vec3(-2.0f, 2.0f, -4.0f))
		.Create(ShapeType::CUBE));

	ShapeManager::shapes.emplace_back(shapesBuilder->ObjectState(CamView::DYNAMIC)
		.SourceType(SourceShapeType::SHAPE)
		.Texture(TEMP_TEXTURE_METAL_EMMISIVE)
		.Shader(LIGHT_TEXTURE_VERT_PATH)
		.Shader(LIGHT_TEXTURE_FRAG_PATH)
		.SetShading(TEXTURE_COLOR)
		.Color(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f))
		.Rotation(glm::vec3(0.0f, 1.0f, 0.0f), glm::radians(1.0f))
		.Position(glm::vec3(0.0f, 1.0f, -8.0f))
		.Create(ShapeType::SPEHERE));

	ShapeManager::shapes.emplace_back(shapesBuilder->ObjectState(CamView::DYNAMIC)
		.SourceType(SourceShapeType::SHAPE)
		.Texture(TEMP_TEXTURE_DIFFUSE)
		.Texture(TEMP_TEXTURE_NORMALMAP)
		.Texture(TEMP_TEXTURE_DISPLACEMENTMAP)
		.Shader(DISPLACEMENT_VERT_PATH)
		.Shader(DISPLACEMENT_FRAG_PATH)
		.SetShading(DISPLACEMENT)
		.Rotation(glm::vec3(1.0f, 0.0f, 0.0f), -90.0f)
		.Position(glm::vec3(3.0f, 0.5f, -3.0f))
		.Create(ShapeType::PLANE));

	ShapeManager::shapes.emplace_back(shapesBuilder->ObjectState(CamView::DYNAMIC)
		.SourceType(SourceShapeType::SHAPE)
		.Texture(TEMP_TEXTURE_DIFFUSE)
		.Shader(LIGHTNING_HDR_VERT)
		.Shader(LIGHTNING_HDR_FRAG)
		.SetShading(HDR_SHADING)
		.SetHDR(true)
		.Rotation(glm::vec3(1.0f, 0.0f, 0.0f), -90.0f)
		.Position(glm::vec3(5.0f, 1.0f, -3.0f))
		.Scale(glm::vec3(2.0f, 2.0f, 1.0f))
		.Create(ShapeType::PLANE));

	ShapeManager::shapes.emplace_back(shapesBuilder->ObjectState(CamView::DYNAMIC)
		.SourceType(SourceShapeType::SHAPE)
		.Shader(PRIMITIVE_VERT_PATH)
		.Shader(PRIMITIVE_FRAG_PATH)
		.PathModel(TEMP_MODEL_PATH)
		.SetShading(Shading::ONLY_COLOR)
		.Color(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f))
		.Position(glm::vec3(3.0f, 1.0f, -8.0f))
		.Create(ShapeType::CUSTOM));

	ShapeManager::shapes.emplace_back(shapesBuilder->ObjectState(CamView::DYNAMIC)
		.SourceType(SourceShapeType::SHAPE)
		.Shader(CUBEBOX_VERT_PATH)
		.Shader(CUBEBOX_FRAG_PATH)
		.Create(ShapeType::SKYBOX));

	//ShapeManager::shapes.push_back(shapesBuilder->ObjectState(CamView::MOVABLE)
	//	.SourceType(SourceShapeType::SHAPE)
	//	.Color(glm::vec4(0.43f, 0.56f, 0.23f, 1.0f))
	//	.Create(ShapeType::LINE));

	TerrainProperties tp = { -4.0f, 1.0f, 16, 16, glm::vec3(0.0f, -4.0f, 0.0f) };
	ShapeManager::shapes.push_back(shapesBuilder->ObjectState(CamView::DYNAMIC)
		.SourceType(SourceShapeType::SHAPE)
		.Texture(TEMP_TEXTURE_GRASS)
		.Shader(TERRAIN_VERT_PATH)
		.Shader(TERRAIN_FRAG_PATH)
		.Shadow(true)
		.CustomProperties(tp)
		.Create(ShapeType::TERRAIN));


	auto filteredShapes = [&](Shading shadingType)
		{
			std::vector<std::shared_ptr<Shape>> shapes;
			for (std::shared_ptr<Shape> shape : ShapeManager::shapes)
			{
				if (shape->GetShading() != shadingType)
					shapes.push_back(shape);
			}
			return shapes;
		};

	std::unique_ptr<LightBuilder> lightBuilder = std::make_unique<LightBuilder>();

	LightManager::lights.push_back(lightBuilder->SetColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f))
		.Position(glm::vec3(-1.9f, -7.5f, 2.0f))
		.Create(LightType::DEFAULT));

	LightManager::lights.push_back(lightBuilder->SetColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f))
		.Position(glm::vec3(5.0f, 1.0f, -3.0f))
		.Create(LightType::DEFAULT));

	//Creation light
	Light* light = new Light();

	for (auto& light : LightManager::lights)
	{
		light->GenerateMVPLight(cam.get());
		light->GenerateLightShaders();
	}

	std::unique_ptr<FrameBufferBuilder> frameBufferBuilder = std::make_unique<FrameBufferBuilder>();
	FrameBufferManager::CreateFRBuffer(FrameBufferType::DEPTHMAP, frameBufferBuilder->AddTexture(TextureMode::SHADOWMAP)
		.Create(FrameBufferType::DEPTHMAP));
	frameBufferBuilder->ResetData();

	FrameBufferManager::CreateFRBuffer(FrameBufferType::POSTPROCESSING, frameBufferBuilder->AddShaderByPath(POSTPROCESSING_VERT_PATH)
		.AddShaderByPath(POSTPROCESSING_FRAG_PATH)
		.AddTexture(TextureMode::FRAMEBUFFER)
		.Create(FrameBufferType::POSTPROCESSING));
	frameBufferBuilder->ResetData();

	FrameBufferManager::CreateFRBuffer(FrameBufferType::HDR, frameBufferBuilder->AddShaderByPath(HDR_VERT_PATH)
		.AddShaderByPath(HDR_FRAG_PATH)
		.AddTexture(TextureMode::HDR_TEXTURE)
		.Create(FrameBufferType::HDR));
	frameBufferBuilder->ResetData();


	FrameBufferManager::CreateFRBuffer(FrameBufferType::HDR, frameBufferBuilder->AddShaderByPath(HDR_GAUSSIANBLUR_VERT_PATH)
		.AddShaderByPath(HDR_GAUSSIANBLUR_FRAG_PATH)
		.AddTexture(TextureMode::HDR_TEXTURE)
		.AddTexture(TextureMode::HDR_TEXTURE)
		.Create(FrameBufferType::BLUR));
	frameBufferBuilder->ResetData();


	FrameBufferManager::CreateFRBuffer(FrameBufferType::GAUUSIAN_HORIZONTAL, frameBufferBuilder->AddShaderByPath(GAUSSIANBLUR_VERT_PATH)
		.AddShaderByPath(GAUSSIANBLUR_FRAG_PATH)
		.AddTexture(TextureMode::HDR_TEXTURE)
		.Create(FrameBufferType::GAUUSIAN_HORIZONTAL));
	frameBufferBuilder->ResetData();

	FrameBufferManager::CreateFRBuffer(FrameBufferType::GAUSSIAN_VERTICAL, frameBufferBuilder->AddShaders(FrameBufferManager::FRbuffer_container[FrameBufferType::GAUUSIAN_HORIZONTAL].frameBuffer->GetFrameBufferShaders())
		.AddTexture(TextureMode::HDR_TEXTURE)
		.Create(FrameBufferType::GAUSSIAN_VERTICAL));

	FrameBufferManager::InitializeFrameBuffers();

	//HDR framebuffer
	FrameBuffer* HDRframeBuffer = new FrameBuffer();
	RenderBuffer* HDRrenderBuffer = new RenderBuffer();
	HDRframeBuffer->Bind();
	HDRframeBuffer->GenerateHDRTextures(2);
	HDRframeBuffer->InitializeHDRShaders();

	HDRrenderBuffer->Bind();
	HDRrenderBuffer->GenerateDepthRenderBuffer();
	HDRrenderBuffer->UnBind();
	HDRrenderBuffer->GenerateDepthFrameRenderBuffer();
	HDRframeBuffer->CheckFrameBuffer();

	HDRframeBuffer->UnBind();

	//Shadow depth map initalizer
	//FrameBuffer* depthMapFrameBuffer = new FrameBuffer();
	//depthMapFrameBuffer->Bind();
	//depthMapFrameBuffer->GenerateShadowTexture();
	//glDrawBuffer(GL_NONE);
	//glReadBuffer(GL_NONE);
	//depthMapFrameBuffer->UnBind();


	//Pingpong Gauss framebuffer
	FrameBuffer* pingpongFramebuffer = new FrameBuffer[2]();
	for (int i = 0; i < 2; ++i)
	{
		pingpongFramebuffer[i].Bind();
		pingpongFramebuffer[i].GenerateHDRTexture();
		pingpongFramebuffer[i].InitializeGaussianBlurShaders();
		pingpongFramebuffer[i].UnBind();
	}

	/// Deffered shading framebuffers

	std::unique_ptr gBuffer = std::make_unique<FrameBuffer>();
	std::unique_ptr gRenderBuffer = std::make_unique<RenderBuffer>();
	gBuffer->Bind();
	std::shared_ptr positionTexture = std::make_shared<Texture>(Texture(0, 0, GL_FLOAT, TextureMode::FRAMEBUFFER));
	std::shared_ptr normalTexture = std::make_shared<Texture>(Texture(1, 1, GL_FLOAT, TextureMode::FRAMEBUFFER));
	std::shared_ptr colorSpecTexture = std::make_shared<Texture>(Texture(2, 2, GL_UNSIGNED_BYTE, TextureMode::FRAMEBUFFER));
	positionTexture->CreateTextureForFrameBuffer();
	normalTexture->CreateTextureForFrameBuffer();
	colorSpecTexture->CreateTextureForFrameBuffer();
	gBuffer->AddTexturesToBuffer({ positionTexture.get(), normalTexture.get(), colorSpecTexture.get() });
	gBuffer->DrawBuffers();
	//gBuffer->InitializeFrameBufferShader(DEFFERED_VERT_PATH, DEFFERED_FRAG_PATH, ShaderTypeGenerator::PassLightMatrixData);
	gRenderBuffer->Bind();
	gRenderBuffer->GenerateDepthRenderBuffer();
	gRenderBuffer->UnBind();
	gRenderBuffer->GenerateDepthFrameRenderBuffer();
	gBuffer->UnBind();


	 
	///add shadow map to shader
	/*Texture* shadowMapRaw = depthMapFrameBuffer->GetFramebufferTexture();
	std::shared_ptr<Texture> shadowMap = std::shared_ptr<Texture>(shadowMapRaw);
	std::vector<std::shared_ptr<Texture>> shadowMapTextureContainer = { shadowMap };*/

	LightManager::InitializeShadowShaders();
	ShapeManager::InitializeShapesData(cam.get());
	//ShapeManager::shapes[1]->SetOutsideLight(ShapeManager::shapes[0]->GetInsideLight());

	cam->InitializeViewProjectionUniformBuffer();
	cam->PassProjectionToShaders();
	cam->PassViewToShaders();



	//Postprocesing initializer
	FrameBuffer* frameBuffer = new FrameBuffer();
	RenderBuffer* renderBuffer = new RenderBuffer();

	frameBuffer->Bind();
	frameBuffer->GenerateTexture();

	frameBuffer->InitializePostProcessingShaders();
	renderBuffer->Bind();
	renderBuffer->GenerateRenderBuffer();
	renderBuffer->UnBind();
	renderBuffer->GenerateFrameRenderBuffer();
	if (!frameBuffer->CheckFrameBuffer())
		std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;


	FrameBuffer::UnBind();

	for (std::shared_ptr<Shape> s : ShapeManager::shapes)
	{
		FrameBufferManager::PassShadowDataToShader(s);
	}
	//Collision initialization TO-DO
	Collision* collision = new Collision();
	collision->objects = ShapeManager::shapes;

	renderer = new Renderer();
	//NOT NEEDED FOR NOW
	//rayDrawer = new RayDrawer();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_STENCIL_TEST);
	glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

	float distance = 1000.0f;

	GLfloat color[] = {
		255, 0, 0
	};

	std::vector<std::shared_ptr<Shape>> selectedShapes;
	auto forwardShapes = filteredShapes(Shading::DEFFERED_SHADING);
	//auto defferedShapes = filteredShapes(Shading::DEFFERED_SHADING);
	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window) && glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS)
	{

		cam->Update();
		/* Render here */
		//HDRframeBuffer->Bind();
		
		if(POSTPROCESSING_EFFECTS)
			FrameBufferManager::FRbuffer_container[POSTPROCESSING].frameBuffer->Bind();

		//Lights
		for (auto& light : LightManager::lights)
		{
			light->Update();
			int verticesCount = light->bm->GetIndexBuffer()->GetCount();
			renderer->Draw(verticesCount, GL_TRIANGLES);
		}
		
		if (HDR_LIGHT)
			FrameBufferManager::FRbuffer_container[HDR].frameBuffer->Bind();



		glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
		FrameBufferManager::FRbuffer_container[DEPTHMAP].frameBuffer->Bind();	
		
		renderer->ClearDepth();
		glEnable(GL_DEPTH_TEST);

		//depthMapFrameBuffer->Bind();
		////renderer->Clear();

		//glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);

		//depthMapFrameBuffer->GetFramebufferTexture()->Bind();
		//
		////render 

		//for (auto& shape : ShapeManager::shapes)
		//{
		//	if (shape->GetSourceShapeType() == SourceShapeType::SHAPE)
		//	{
		//		shape->UpdateLight();
		//		shape->ActivateShapeBufferParts();
		//		int verticesCount = shape->bm->GetIndexBuffer()->GetCount();
		//		auto terr = dynamic_cast<Terrain*>(shape.get());
		//		if (terr == nullptr)
		//		{
		//			renderer->Draw(verticesCount, GL_TRIANGLES);
		//		}
		//		else
		//			renderer->DrawArrayInstances(verticesCount, GL_TRIANGLE_STRIP, 256);

		//		shape->DeactivateShapeBufferParts();
		//	}

		//}


		//FrameBuffer::UnBind();
		//renderer->Clear();
		//glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

		//FrameBuffer::UnBind();


		//TO-DO SET THIS LIGHTNING SHAPES
		for (auto& shape : ShapeManager::shapes)
		{
			if(shape->IsShadowTurnOn())
			{
				if (auto terr = dynamic_cast<Terrain*>(shape.get()))
					LightManager::CreateShadowForLightsTerrain(std::static_pointer_cast<Terrain>(shape));
				else
					LightManager::CreateShadowForLights(shape);
				int verticesCount = shape->bm->GetIndexBuffer()->GetCount();
				renderer->Draw(verticesCount, GL_TRIANGLES);
				shape->DeactivateShapeBufferParts();
			}
		}

		FrameBufferManager::FRbuffer_container[DEPTHMAP].frameBuffer->UnBind();

		glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
		renderer->Clear();
		
		//int count = 0;

		glStencilMask(0x00);

		glClearColor(0.0f, 0.2f, 0.0f, 1.0f);

		//Shapes
		//for (auto& shape : ShapeManager::shapes)
		//{
		//	if (shape->Selected)
		//	{
		//		selectedShapes.push_back(shape);
		//		continue;
		//	}
		//}

		////deffered
		//for (auto& shape : defferedShapes)
		//{
		//	shape->ApplyShapeView(cam->GetView());
		//	shape->SetEyeCamPos(cam->GetCamPos());
		//	shape->SetOutsideLight(light->Position);
		//	shape->Update();
		//	if (shape->GetSourceShapeType() != SourceShapeType::PRIMITIVE)
		//	{
		//		auto terr = dynamic_cast<Terrain*>(shape.get());
		//		int verticesCount = shape->bm->GetIndexBuffer()->GetCount();
		//		if (terr == nullptr)
		//		{
		//			renderer->Draw(verticesCount, GL_TRIANGLES);
		//		}
		//		else
		//			renderer->DrawArrayInstances(verticesCount, GL_TRIANGLE_STRIP, 256);

		//	}
		//	shape->AfterUpdate();
		//	shape->DeactivateShapeBufferParts();
		//}

		//forward
		for (auto& shape : forwardShapes)
		{

			/// view is not needed in shapes ;)
			//shape->ApplyShapeView(cam->GetView());
			//shape->SetEyeCamPos(cam->GetCamPos());

			if (shape->Selected)
			{
				selectedShapes.push_back(shape);
				continue;
			}

			shape->SetMainLight(light->Position);
			shape->Update();
			if (shape->GetSourceShapeType() != SourceShapeType::PRIMITIVE)
			{
				auto terr = dynamic_cast<Terrain*>(shape.get());
				int verticesCount = shape->bm->GetIndexBuffer()->GetCount();
				if (terr == nullptr)
				{
					renderer->Draw(verticesCount, GL_TRIANGLES);
				}
				else
					renderer->DrawArrayInstances(verticesCount, GL_TRIANGLE_STRIP, 256);

			}
			shape->AfterUpdate();
			//Check collision - for now on main loop
			collision->CheckCollision();

			/*if (dynamic_cast<Primitive*>(shape) != nullptr)
			{
				Primitive* p = dynamic_cast<Primitive*>(shape);
				delete p;
			}*/
			shape->AfterUpdate();
		}

		//Selected shapes
		for (auto& sShape : selectedShapes)
		{
			// draw selection
			TurnOnStencilBufferMask();
			sShape->Update();
			renderer->Draw(sShape->bm->GetIndexBuffer()->GetCount(), GL_TRIANGLES);
			sShape->DeactivateShapeBufferParts();

			//draw object
			TurnOnNormalMask();
			glDisable(GL_DEPTH_TEST);
			sShape->UpdatePickedShape();
			renderer->Draw(sShape->bm->GetIndexBuffer()->GetCount(), GL_TRIANGLES);
			sShape->DeactivateShapeBufferParts();
			TurnOffStencilBufferMask();
			glEnable(GL_DEPTH_TEST);
		}
		glDisable(GL_DEPTH_TEST);

		//FrameBuffer::UnBind();

		//bool horizontal = true, firstIteration = true;
		//int amount = 10;

		//for (unsigned int i = 0; i < amount; i++)
		//{
		//	pingpongFramebuffer[horizontal].Bind();
		//	pingpongFramebuffer[horizontal].TurnOnFrameBufferElements();
		//	pingpongFramebuffer[horizontal].UpdateGaussianBlurShaders(horizontal);
		//	if (firstIteration)
		//		HDRframeBuffer->GetFramebufferTextures()[1]->Bind();
		//	else
		//		pingpongFramebuffer[!horizontal].GetFramebufferTexture()->Bind();

		//	renderer->DrawArrays(6, GL_TRIANGLES);

		//	horizontal = !horizontal;
		//	if (firstIteration)
		//		firstIteration = false;
		//}

		//FrameBuffer::UnBind();

		//renderer->Clear();
		//HDRframeBuffer->GetFramebufferTexture()->Bind();
		//HDRframeBuffer->TurnOnFrameBufferElements();
		////renderer->Clear();
		//pingpongFramebuffer[!horizontal].GetFramebufferTexture()->BindTexture(1);
		//HDRframeBuffer->TurnOnFrameBufferElements();
		//renderer->DrawArrays(6, GL_TRIANGLES);


		//works fine
		if (POSTPROCESSING_EFFECTS)
		{
			FrameBufferManager::FRbuffer_container[POSTPROCESSING].frameBuffer->UnBind();
			FrameBufferManager::FRbuffer_container[POSTPROCESSING].frameBuffer->TurnOffFrameBufferElements();
			glDisable(GL_DEPTH_TEST);
			renderer->ClearColor();
			FrameBufferManager::FRbuffer_container[POSTPROCESSING].frameBuffer->TurnOnFrameBufferElements();
			FrameBufferManager::FRbuffer_container[POSTPROCESSING].frameBuffer->GetFramebufferTexture()->Bind();
			renderer->DrawArrays(6, GL_TRIANGLES);
		}
		
		selectedShapes.clear();
		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();

	//delete renderBuffer;
	delete frameBuffer;
	delete HDRframeBuffer;
	//delete depthMapFrameBuffer;
	delete window;

	return 0;
}
OpenGLGameWindow::~OpenGLGameWindow()
{
	delete renderer;
	delete this;
}

void TurnOnStencilBufferMask()
{
	glStencilFunc(GL_ALWAYS, 1, 0xFF);
	glStencilMask(0xFF);
}

void TurnOffStencilBufferMask()
{
	glStencilFunc(GL_ALWAYS, 0, 0xFF);
	glStencilMask(0xFF);
}

void TurnOnNormalMask()
{
	glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
	glStencilMask(0x00);
}

