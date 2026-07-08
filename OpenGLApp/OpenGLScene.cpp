#include <vector>
#include <typeinfo>

#include "OpenGLScene.h"
#include "Managers/FrameBufferManager.h"
#include "PlaneView.h"


namespace AppEngine
{
	// to-do do textures for framebuffer (maybe class or something like that) to prepare connection beetween framebuffers
	// rewrite activate and deactivate binding textures with slots, set function colorattachment

	RayDrawer* rayDrawer;
	static ThreadPool threadPool(std::thread::hardware_concurrency());
	OpenGLScene::OpenGLScene(GLFWwindow* window) : window(window)
	{
		CreateScene();
	}

	int OpenGLScene::CreateScene()
	{
		// Creation window
		//if (!glfwInit())
		//	return -1;

		//glfwWindowHint(GLFW_SAMPLES, 4);

		//window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Hello World", NULL, NULL);
		//if (!window)
		//{
		//	glfwTerminate();
		//	return -1;
		//}

		//// OpenGL params

		//glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		//glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
		//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		///* Make the window's context current */
		//glfwMakeContextCurrent(window);
		//// glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		//GLenum err = glewInit();
		//if (GLEW_OK != err)
		//{
		//	return -1;
		//}
		//glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);


		/* Set cameras */
		auto camManager = CameraManager::GetInstance();
		cam = std::make_shared<Camera>();
		glm::vec3 camProps[3] = {
			glm::vec3(0.0f, 0.0f, 0.0f), // position
			glm::vec3(0.0f, 0.0f, -1.0f), // looking
			glm::vec3(0.0f, 1.0f, 0.0f) // up direction
		};
		cam->CreateView(camProps, 5.0f, window);
		camManager->AddCamera(cam.get());
		camManager->SetActiveCamera(cam.get());



		Controls* control = new Controls(window);
		/* Creation all objects in scene */
		std::unique_ptr<ShapesBuilder> shapesBuilder = std::make_unique<ShapesBuilder>();

		ShapeManager::shapes.emplace_back(shapesBuilder->ObjectState(CamView::DYNAMIC)
			.SourceType(SourceShapeType::SHAPE)
			.Shader(CUBEBOX_VERT_PATH)
			.Shader(CUBEBOX_FRAG_PATH)
			.SetShading(Shading::CUBEMAP)
			.Create(ShapeType::SKYBOX));

		ShapeManager::shapes.emplace_back(shapesBuilder->ObjectState(CamView::DYNAMIC)
			.SourceType(SourceShapeType::SHAPE)
			.Texture(TEMP_TEXTURE_DIFFUSE)
			.Texture(TEMP_TEXTURE_SPECULAR)
			.Shader(DIFFUSE_VERT_PATH)
			.Shader(DIFFUSE_FRAG_PATH)
			.Shadow(false)
			.Position(glm::vec3(0.6f, 0.12f, -3.0f))
			.Create(ShapeType::CUBE));

		ShapeManager::shapes.emplace_back(shapesBuilder->ObjectState(CamView::DYNAMIC)
			.SourceType(SourceShapeType::SHAPE)
			.Texture(TEMP_TEXTURE_DIFFUSE)
			.Texture(TEMP_TEXTURE_SPECULAR)
			.Shader(DIFFUSE_VERT_PATH)
			.Shader(DIFFUSE_FRAG_PATH)
			.Shadow(false)
			.Rotation(glm::vec3(0.0f, 0.0f, 0.0f), 0.0f)
			.Position(glm::vec3(0.0f, -1.0f, -3.0f))
			.Scale(glm::vec3(5.0f, 1.0f, 5.0f))
			.Create(ShapeType::PLANE));

		ShapeManager::shapes.emplace_back(shapesBuilder->ObjectState(CamView::DYNAMIC)
			.SourceType(SourceShapeType::SHAPE)
			.Texture(TEMP_TEXTURE_DIFFUSE)
			.Texture(TEMP_TEXTURE_SPECULAR)
			.Shader(GBUFFER_VERT_PATH)
			.Shader(GBUFFER_FRAG_PATH)
			.SetShading(Shading::DEFFERED_SHADING)
			.Position(glm::vec3(-2.0f, 2.0f, -4.0f))
			.Create(ShapeType::CUBE));

		//ShapeManager::shapes.emplace_back(shapesBuilder->ObjectState(CamView::DYNAMIC)
		//	.SourceType(SourceShapeType::SHAPE)
		//	.Shader(GBUFFER_VERT_PATH)
		//	.Shader(GBUFFER_FRAG_PATH)
		//	.SetShading(Shading::DEFFERED_SHADING)
		//	.Color(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f))
		//	.Position(glm::vec3(0.0f, 2.0f, -6.0f))
		//	.Rotation(glm::vec3(1.0f, 0.0f, 0.0f), -90.0f)
		//	.Scale(glm::vec3(5.0f, 5.0f, 1.0f))
		//	.Create(ShapeType::PLANE));

		ShapeManager::shapes.emplace_back(shapesBuilder->ObjectState(CamView::DYNAMIC)
			.SourceType(SourceShapeType::SHAPE)
			.Texture(TEMP_TEXTURE_DIFFUSE)
			.Texture(TEMP_TEXTURE_SPECULAR)
			.Shader(GBUFFER_VERT_PATH)
			.Shader(GBUFFER_FRAG_PATH)
			.SetShading(Shading::DEFFERED_SHADING)
			.Position(glm::vec3(1.0f, 2.0f, -3.0f))
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

		//ShapeManager::shapes.emplace_back(shapesBuilder->ObjectState(CamView::DYNAMIC)
		//	.SourceType(SourceShapeType::SHAPE)
		//	.Texture(TEMP_TEXTURE_DIFFUSE)
		//	.Shader(LIGHTNING_HDR_VERT)
		//	.Shader(LIGHTNING_HDR_FRAG)
		//	.SetShading(HDR_SHADING)
		//	.SetHDR(true)
		//	.Rotation(glm::vec3(1.0f, 0.0f, 0.0f), -90.0f)
		//	.Position(glm::vec3(5.0f, 1.0f, -3.0f))
		//	.Scale(glm::vec3(2.0f, 2.0f, 1.0f))
		//	.Create(ShapeType::PLANE));

		ShapeManager::shapes.emplace_back(shapesBuilder->ObjectState(CamView::DYNAMIC)
			.SourceType(SourceShapeType::SHAPE)
			.Shader(PRIMITIVE_VERT_PATH)
			.Shader(PRIMITIVE_FRAG_PATH)
			.PathModel(TEMP_MODEL_PATH)
			.SetShading(Shading::ONLY_COLOR)
			.Color(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f))
			.Position(glm::vec3(3.0f, 1.0f, -4.0f))
			.Create(ShapeType::CUSTOM));

		//ShapeManager::shapes.push_back(shapesBuilder->ObjectState(CamView::MOVABLE)
		//	.SourceType(SourceShapeType::SHAPE)
		//	.Color(glm::vec4(0.43f, 0.56f, 0.23f, 1.0f))
		//	.Create(ShapeType::LINE));

		TerrainProperties tp = { -4.0f, 1.0f, 16, 16, glm::vec3(0.0f, -3.0f, 0.0f) };
		ShapeManager::shapes.push_back(shapesBuilder->ObjectState(CamView::DYNAMIC)
			.SourceType(SourceShapeType::SHAPE)
			.Texture(TEMP_TEXTURE_GRASS)
			.Shader(TERRAIN_VERT_PATH)
			.Shader(TERRAIN_FRAG_PATH)
			.Shadow(true)
			.CustomProperties(tp)
			.Create(ShapeType::TERRAIN));

		std::unique_ptr<LightBuilder> lightBuilder = std::make_unique<LightBuilder>();

		LightManager::lights.push_back(lightBuilder->SetColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f))
			.Position(glm::vec3(2.5f, 2.5f, -2.5f))
			.Create(LightType::DEFAULT));

		LightManager::lights.push_back(lightBuilder->SetColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f))
			.Position(glm::vec3(-2.0f, 1.0f, -3.0f))
			.Create(LightType::DEFAULT));

		//Creation light

		for (auto& light : LightManager::lights)
		{
			light->GenerateMVPLight(cam.get());
			light->GenerateLightShaders();
		}
		mainLight = LightManager::lights[0].get();



		std::unique_ptr<FrameBufferBuilder> frameBufferBuilder = std::make_unique<FrameBufferBuilder>();

		FrameBufferManager::CreateFRBuffer(FrameBufferType::MAIN, frameBufferBuilder->AddTexture(TextureMode::FRAMEBUFFER)
			.AddShaderByPath(MAIN_TEXTURE_RENDER_VERT)
			.AddShaderByPath(MAIN_TEXTURE_RENDER_FRAG)
			.Create(FrameBufferType::MAIN));
		frameBufferBuilder->ResetData();
		auto mainFBOHandler = FrameBufferManager::FRbuffer_container[MAIN].frameBuffer->GetFrameBuffer();

		FrameBufferManager::CreateFRBuffer(FrameBufferType::DEPTHMAP, frameBufferBuilder->AddTexture(TextureMode::SHADOWMAP)
			.RenderTarget(mainFBOHandler)
			.Create(FrameBufferType::DEPTHMAP));
		frameBufferBuilder->ResetData();

		FrameBufferManager::CreateFRBuffer(FrameBufferType::POSTPROCESSING, frameBufferBuilder->AddShaderByPath(POSTPROCESSING_VERT_PATH)
			.RenderTarget(mainFBOHandler)
			.AddShaderByPath(POSTPROCESSING_FRAG_PATH)
			.AddTexture(TextureMode::FRAMEBUFFER)
			.Create(FrameBufferType::POSTPROCESSING));
		frameBufferBuilder->ResetData();

		FrameBufferManager::CreateFRBuffer(FrameBufferType::HDR, frameBufferBuilder->AddShaderByPath(HDR_VERT_PATH)
			.RenderTarget(mainFBOHandler)
			.AddShaderByPath(HDR_FRAG_PATH)
			.AddTexture(TextureMode::HDR_TEXTURE)
			.Create(FrameBufferType::HDR));
		frameBufferBuilder->ResetData();


		FrameBufferManager::CreateFRBuffer(FrameBufferType::BLUR, frameBufferBuilder->AddShaderByPath(HDR_GAUSSIANBLUR_VERT_PATH)
			.RenderTarget(mainFBOHandler)
			.AddShaderByPath(HDR_GAUSSIANBLUR_FRAG_PATH)
			.AddTexture(TextureMode::HDR_TEXTURE, 0, 0)
			.AddTexture(TextureMode::HDR_TEXTURE, 0, 1)
			.Create(FrameBufferType::BLUR));
		frameBufferBuilder->ResetData();


		FrameBufferManager::CreateFRBuffer(FrameBufferType::GAUSSIAN_HORIZONTAL, frameBufferBuilder->AddShaderByPath(GAUSSIANBLUR_VERT_PATH)
			.RenderTarget(mainFBOHandler)
			.AddShaderByPath(GAUSSIANBLUR_FRAG_PATH)
			.AddTexture(TextureMode::HDR_TEXTURE, 0)
			.Create(FrameBufferType::GAUSSIAN_HORIZONTAL));
		frameBufferBuilder->ResetData();

		FrameBufferManager::CreateFRBuffer(FrameBufferType::GBUFFER, frameBufferBuilder->AddShaderByPath(DEFFERED_VERT_PATH)
			.RenderTarget(mainFBOHandler)
			.AddShaderByPath(DEFFERED_FRAG_PATH)
			.AddTexture(TextureMode::G_BUFFER_TRANSFORM, 0, 0)
			.AddTexture(TextureMode::G_BUFFER_NORMAL, 0, 1)
			.AddTexture(TextureMode::G_BUFFER_COLOR_SPECULAR, 0, 2)
			.Create(FrameBufferType::GBUFFER));
		frameBufferBuilder->ResetData();

		FrameBufferManager::CreateFRBuffer(FrameBufferType::SSAO, frameBufferBuilder->AddShaderByPath(SSAO_VERT_PATH)
			.RenderTarget(mainFBOHandler)
			.AddShaderByPath(SSAO_FRAG_PATH)
			.AddTexture(TextureMode::ONE_COLOR, 0, 0)
			.Create(FrameBufferType::SSAO));
		frameBufferBuilder->ResetData();

		FrameBufferManager::CreateFRBuffer(FrameBufferType::SSAO_LIGHTNING, frameBufferBuilder->AddShaderByPath(SSAO_LIGHTNING_VERT_PATH)
			.RenderTarget(mainFBOHandler)
			.AddShaderByPath(SSAO_LIGHTNING_FRAG_PATH)
			.AddTexture(TextureMode::FRAMEBUFFER)
			.Create(FrameBufferType::SSAO_LIGHTNING));

		frameBufferBuilder->ResetData();


		FrameBufferManager::InitializeFrameBuffers(mainFBOHandler);
		LightManager::AddLightsToFrameBuffer(FrameBufferManager::FRbuffer_container[GBUFFER].frameBuffer);
		LightManager::AddLightsToFrameBuffer(FrameBufferManager::FRbuffer_container[SSAO_LIGHTNING].frameBuffer);

		/// generate samples for SSAO
		KernelSamplerGenerator kernelSampler;
		std::vector<glm::vec3> ssaoKernel = kernelSampler.GenerateKernelSamples();
		Texture* ssaoNoiseTexture = new Texture(2, 0, 5126, TEXTURE, 4, 4);
		ssaoNoiseTexture->CreateNoiseTexture();
		FrameBufferManager::AddKernelSamplesToSSAOBuffer(ssaoKernel);

		for (auto fb : FrameBufferManager::FRbuffer_container)
		{
			fb.second.frameBuffer->InitializeShaders();
		}

		LightManager::InitializeShadowShaders();
		ShapeManager::InitializeShapesData(cam.get());
		//ShapeManager::shapes[1]->SetOutsideLight(ShapeManager::shapes[0]->GetInsideLight());

		cam->InitializeViewProjectionUniformBuffer();
		cam->PassProjectionToShaders();
		cam->PassViewToShaders();


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
		glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

		std::vector<std::shared_ptr<Shape>> selectedShapes;
		skyboxShape = dynamic_cast<SkyBoxCube*>(ShapeManager::FilterShape(Shading::CUBEMAP)[0].get());
		terrainShape = dynamic_cast<Terrain*>(ShapeManager::FilterShape(ShapeType::TERRAIN)[0].get());
		forwardShapes = ShapeManager::FilterShape({ Shading::FORWARD_SHADING, Shading::DISPLACEMENT, Shading::TEXTURE_COLOR, Shading::DISPLACEMENT,
			Shading::ONLY_COLOR });
		deferredShapes = ShapeManager::FilterShape(Shading::DEFFERED_SHADING);
		shadowShapes = ShapeManager::FilterShape(true);

		bool horizontal = true;

		ShaderProperties sp;
		sp.type = ShaderFunctionType::SHADER_FUNC_BLOOM;
		sp.params.push_back(0.9f);
		Paths paths;
		paths.shadersPaths = { HDR_GAUSSIANBLUR_VERT_PATH, HDR_GAUSSIANBLUR_FRAG_PATH };
		screen = new RendererScreen(paths, sp);

		futures.reserve(forwardShapes.size());
		/* Loop until the user closes the window */

		/// TO-DO refactor this code, maybe create some functions for each step of rendering, and make it more clear and readable
		return 0;
	}

	std::shared_ptr<FrameBuffer> OpenGLScene::RenderScene(ImVec2 size, ImVec2 position)
	{
		renderer->Clear();
		cam->Update();
		glStencilMask(0x00);
		auto& mainFBO = FrameBufferManager::FRbuffer_container[MAIN].frameBuffer;
		mainFBO->Bind();

		if (POSTPROCESSING_EFFECTS)
		{
			FrameBufferManager::FRbuffer_container[POSTPROCESSING].frameBuffer->Bind();
			renderer->Clear();
		}

		if (HDR_LIGHT)
			FrameBufferManager::FRbuffer_container[HDR].frameBuffer->Bind();

		if (SHADOW)
		{
			glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
			FrameBufferManager::FRbuffer_container[DEPTHMAP].frameBuffer->Bind();

			renderer->ClearDepth();
			glEnable(GL_DEPTH_TEST);


			//TO-DO SET THIS LIGHTNING SHAPES
			for (auto& shape : shadowShapes)
			{
				if (auto terr = dynamic_cast<Terrain*>(shape.get()))
					LightManager::CreateShadowForLightsTerrain(std::static_pointer_cast<Terrain>(shape));
				else
					LightManager::CreateShadowForLights(shape);
				int verticesCount = shape->bm->GetIndexBuffer()->GetCount();
				renderer->Draw(verticesCount, GL_TRIANGLES);
				shape->DeactivateShapeBufferParts();
			}

			mainFBO->Bind();

			//to-do pass gui screen size
			glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
			renderer->ClearColor();
			renderer->ClearDepth();
		}

		if (GAUSSIAN_BLUR)
		{
			FrameBufferManager::FRbuffer_container[BLUR].frameBuffer->Bind();
			renderer->Clear();
		}

		mainFBO->Bind();
		glEnable(GL_DEPTH_TEST);
		glDisable(GL_BLEND);


		glDepthFunc(GL_LEQUAL);
		glDepthMask(GL_FALSE);

		skyboxShape->SetMainLight(mainLight->Position);
		skyboxShape->Update();
		renderer->Draw(skyboxShape->bm->GetIndexBuffer()->GetCount(), GL_TRIANGLES);
		skyboxShape->AfterUpdate();

		terrainShape->SetMainLight(mainLight->Position);
		terrainShape->Update();
		renderer->DrawArrayInstances(terrainShape->bm->GetIndexBuffer()->GetCount(), GL_TRIANGLE_STRIP, 256);
		terrainShape->AfterUpdate();

		for (auto& shape : ShapeManager::shapes)
		{
			if (shape->Selected)
			{
				selectedShapes.push_back(shape);
				continue;
			}
		}

		glDepthMask(GL_TRUE);
		glDepthFunc(GL_LESS);

		//deffered
		FrameBufferManager::FRbuffer_container[GBUFFER].frameBuffer->Bind();
		renderer->ClearColor();
		renderer->Clear();
		for (auto& shape : deferredShapes)
		{
			shape->SetMainLight(mainLight->Position);
			shape->Update();
			int verticesCount = shape->bm->GetIndexBuffer()->GetCount();
			renderer->Draw(verticesCount, GL_TRIANGLES);
			shape->AfterUpdate();
		}
		mainFBO->Bind();

		if (SSAO_LIGHT)
		{
			FrameBufferManager::FRbuffer_container[SSAO].frameBuffer->Bind();
			renderer->ClearColor();
			FrameBufferManager::FRbuffer_container[SSAO].frameBuffer->BindDrawBuffers();

			for (int i = 0; i < FrameBufferManager::FRbuffer_container[GBUFFER].frameBuffer->GetFramebufferTextures().size() - 1; i++)
			{
				FrameBufferManager::FRbuffer_container[GBUFFER].frameBuffer->GetFramebufferTexture(i)->Bind(i);
			}
			ssaoNoiseTexture->Bind(2);


			FrameBufferManager::FRbuffer_container[SSAO].frameBuffer->UpdateFrameBuffer();
			renderer->DrawArrays(6, GL_TRIANGLES);
			FrameBufferManager::FRbuffer_container[SSAO].frameBuffer->AfterUpdateFrameBuffer();

			FrameBufferManager::FRbuffer_container[SSAO].frameBuffer->UnBindDrawBuffers();
			mainFBO->Bind();


			//lightning pass with SSAO

			FrameBufferManager::FRbuffer_container[SSAO_LIGHTNING].frameBuffer->Bind();
			renderer->Clear();
			FrameBufferManager::FRbuffer_container[SSAO_LIGHTNING].frameBuffer->BindDrawBuffers();

			for (int i = 0; i < FrameBufferManager::FRbuffer_container[GBUFFER].frameBuffer->GetFramebufferTextures().size(); i++)
			{
				FrameBufferManager::FRbuffer_container[GBUFFER].frameBuffer->GetFramebufferTexture(i)->Bind(i);
			}

			FrameBufferManager::FRbuffer_container[SSAO].frameBuffer->GetFramebufferTexture(0)->Bind(3); // SSAO texture

			FrameBufferManager::FRbuffer_container[SSAO_LIGHTNING].frameBuffer->UpdateFrameBuffer();
			renderer->DrawArrays(6, GL_TRIANGLES);
			FrameBufferManager::FRbuffer_container[SSAO_LIGHTNING].frameBuffer->AfterUpdateFrameBuffer();

			FrameBufferManager::FRbuffer_container[SSAO_LIGHTNING].frameBuffer->UnBindDrawBuffers();
			mainFBO->Bind();

			// set state for full-screen pass
			glDisable(GL_DEPTH_TEST);
			glDisable(GL_BLEND);
			glDisable(GL_STENCIL_TEST);


			//Activate SSAO_LIGHTNING framebuffer as "presenter"
			FrameBuffer* ssaoLightFB = FrameBufferManager::FRbuffer_container[SSAO_LIGHTNING].frameBuffer.get();
			FrameBuffer* gbufferFB = FrameBufferManager::FRbuffer_container[GBUFFER].frameBuffer.get();
			FrameBuffer* ssaoFB = FrameBufferManager::FRbuffer_container[SSAO].frameBuffer.get();

			// 1) Prepare the SSAO_LIGHTNING pass: enable its shader/quad
			ssaoLightFB->BindDrawBuffers(); // enables shader program, binds quad VAO

			// 2) Bind inputs to the units expected by the SSAO_LIGHTNING shader.
			//    Ensure sampler uniform indices in that shader match these unit numbers.
			if (gbufferFB)
			{
				auto gTextures = gbufferFB->GetFramebufferTextures();
				for (int i = 0; i < (int)gTextures.size(); ++i)
				{
					if (gTextures[i]) gTextures[i]->Bind(i); // gPosition->0, gNormal->1, gAlbedoSpec->2 ...
				}
			}
			if (ssaoFB && ssaoFB->GetFramebufferTexture(0))
			{
				ssaoFB->GetFramebufferTexture(0)->Bind(3); // ssao -> unit 3 (adjust if your shader expects different unit)
			}

			// 3) Let the framebuffer's shader set its uniforms (light positions, etc.)
			ssaoLightFB->UpdateFrameBuffer(); // this should call your ShaderTypeGenerator::Update (sets uniforms)

			// 4) Draw the full-screen quad (your renderer draws 6 verts quad)
			renderer->DrawArrays(6, GL_TRIANGLES);

			//5) Cleanup (unbind shader/quad)
			ssaoLightFB->AfterUpdateFrameBuffer();

			// restore GL state
			glEnable(GL_DEPTH_TEST);
			glEnable(GL_BLEND);
			glEnable(GL_STENCIL_TEST);

			mainFBO->Bind();
		}
		else
		{
			FrameBufferManager::FRbuffer_container[GBUFFER].frameBuffer->BindDrawBuffers();
			for (int i = 0; i < FrameBufferManager::FRbuffer_container[GBUFFER].frameBuffer->GetFramebufferTextures().size(); i++)
			{
				FrameBufferManager::FRbuffer_container[GBUFFER].frameBuffer->GetFramebufferTextures()[i]->Bind(i);
			}

			FrameBufferManager::FRbuffer_container[GBUFFER].frameBuffer->UpdateFrameBuffer();

			renderer->DrawArrays(6, GL_TRIANGLES);
			FrameBufferManager::FRbuffer_container[GBUFFER].frameBuffer->AfterUpdateFrameBuffer();

			FrameBufferManager::FRbuffer_container[GBUFFER].frameBuffer->ReadBind();
			mainFBO->DrawBind();
			glBlitFramebuffer(position.x, position.y, size.x, size.y, position.x, position.y, size.x, size.y, GL_DEPTH_BUFFER_BIT, GL_NEAREST);
			mainFBO->Bind();
		}
		//Lights
		if (LIGHT_OBJECTS)
		{
			glEnable(GL_BLEND);
			glBlendFunc(GL_ONE, GL_ONE);

			for (auto& light : LightManager::lights)
			{
				light->Update();
				int verticesCount = light->bm->GetIndexBuffer()->GetCount();
				renderer->Draw(verticesCount, GL_TRIANGLES);
			}

			glDisable(GL_BLEND);
			glEnable(GL_DEPTH_TEST);
		}

		for (size_t i = 0; i < forwardShapes.size(); ++i)
		{
			auto& shapePtr = forwardShapes[i];
			futures.emplace_back(threadPool.Enqueue([shapePtr]()
				{
					shapePtr->CalculateMath();
				}));

		}

		for (auto& f : futures)
		{
			try
			{
				f.get();
			}
			catch (const std::exception& e)
			{
				std::cerr << "Worker exception: " << e.what() << '\n';
			}
		}

		futures.clear();


		for (auto& shape : forwardShapes)
		{
			if (!shape->Selected)
			{
				shape->SetMainLight(mainLight->Position);
				shape->Update();
				int verticesCount = shape->bm->GetIndexBuffer()->GetCount();
				renderer->Draw(verticesCount, GL_TRIANGLES);
				shape->AfterUpdate();
			}
		}


		///Selected shapes
		//renderer->ClearStencil();
		for (auto& sShape : selectedShapes)
		{
			// draw selection
			glEnable(GL_DEPTH_TEST);
			glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
			glStencilFunc(GL_ALWAYS, 1, 0xFF);
			glStencilMask(0xFF);
			sShape->Update();
			renderer->Draw(sShape->bm->GetIndexBuffer()->GetCount(), GL_TRIANGLES);
			sShape->DeactivateShapeBufferParts();
			sShape->AfterUpdate();

			/// draw selected shape
			glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
			glStencilMask(0x00);
			glDisable(GL_DEPTH_TEST);
			glStencilMask(0x00);
			sShape->UpdatePickedShape();
			renderer->Draw(sShape->bm->GetIndexBuffer()->GetCount(), GL_TRIANGLES);
			sShape->DeactivateShapeBufferParts();
			sShape->AfterUpdate();
			glStencilMask(0xFF);
			glEnable(GL_DEPTH_TEST);
		}




		// Fix for the initialization issue with FrameBufferType and bool
		if (GAUSSIAN_BLUR)
		{
			mainFBO->Bind();
			FrameBufferManager::FRbuffer_container[BLUR].frameBuffer->UnBindDrawBuffers();
			//glDisable(GL_DEPTH_TEST);
			bool firstIteration = true, horizontal = true;
			for (int i = 0; i < 8; ++i)
			{
				FrameBufferManager::FRbuffer_container[static_cast<FrameBufferType>(horizontal)].frameBuffer->Bind();

				if (firstIteration)
				{
					FrameBufferManager::FRbuffer_container[BLUR].frameBuffer->GetFramebufferTexture(1)->Bind();
					firstIteration = false;
				}
				else
				{
					FrameBufferManager::FRbuffer_container[static_cast<FrameBufferType>(horizontal)].frameBuffer->GetFramebufferTexture(0)->Bind(0);
				}

				FrameBufferManager::FRbuffer_container[static_cast<FrameBufferType>(horizontal)].frameBuffer->BindDrawBuffers();

				// ustawiamy uniform horizontal = true
				//FrameBufferManager::FRbuffer_container[GAUUSIAN_HORIZONTAL].frameBuffer->TurnOnFrameBufferElements();

				renderer->DrawArrays(6, GL_TRIANGLES);
				FrameBufferManager::FRbuffer_container[static_cast<FrameBufferType>(horizontal)].frameBuffer->UnBindDrawBuffers();
				//
				//horizontal = !horizontal;
			}
			mainFBO->Bind();

			renderer->Clear();
			FrameBufferManager::FRbuffer_container[BLUR].frameBuffer->GetFramebufferTexture(0)->Bind(0);
			//FrameBufferManager::FRbuffer_container[GAUSSIAN_HORIZONTAL].frameBuffer->GetFramebufferTexture(0)->Bind(0);
			FrameBufferManager::FRbuffer_container[BLUR].frameBuffer->BindDrawBuffers();


			//ScreenBlock for test next will be on whole loop 
			// TO-DO make texture handler for adding textures to screen renderer
			FrameBufferManager::FRbuffer_container[BLUR].frameBuffer->GetFramebufferTexture()->Bind(0);
			FrameBufferManager::FRbuffer_container[static_cast<FrameBufferType>(horizontal)].frameBuffer->GetFramebufferTexture(0)->Bind(1);
			screen->Update();
			renderer->DrawArrays(6, GL_TRIANGLES);
			screen->AfterUpdate();
		}
		if (HDR_LIGHT)
		{
			mainFBO->Bind();
			FrameBufferManager::FRbuffer_container[HDR].frameBuffer->UnBindDrawBuffers();
			glDisable(GL_DEPTH_TEST);
			renderer->ClearColor();
			FrameBufferManager::FRbuffer_container[HDR].frameBuffer->BindDrawBuffers();
			renderer->DrawArrays(6, GL_TRIANGLES);
		}
		if (POSTPROCESSING_EFFECTS)
		{
			mainFBO->Bind();
			glDisable(GL_DEPTH_TEST);
			renderer->Clear();
			FrameBufferManager::FRbuffer_container[POSTPROCESSING].frameBuffer->BindDrawBuffers();
			FrameBufferManager::FRbuffer_container[POSTPROCESSING].frameBuffer->GetFramebufferTexture()->Bind();
			renderer->DrawArrays(6, GL_TRIANGLES);

			FrameBufferManager::FRbuffer_container[POSTPROCESSING].frameBuffer->UnBindDrawBuffers();
		}

		glDisable(GL_BLEND);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		selectedShapes.clear();
		return mainFBO;

	}
	OpenGLScene::~OpenGLScene()
	{
		delete renderer;
		delete this;
	}
}