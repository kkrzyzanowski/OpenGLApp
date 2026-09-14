#pragma once
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <iostream>
#include <future>
#include "GameWindow.h"
#include "Shapes\Shape.h"
#include "Shaders\ShaderClasses\Shader.h"
#include "Managers\ShapeManager.h"
#include "Rendering\Renderer.h"
#ifndef LIGHT_LIBRARY
#define LIGHT_LIBRARY
#endif // !LIGHT

#include "Managers\ShaderCompiler.h"
#include "Camera\Camera.h"
#include "Buffers\FrameBuffer.h"
#include "Config.h"
#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtc\type_ptr.hpp"
#include "Shapes\SkyBoxCube.h"
#include "Controls.h"
#include "Camera\RayDrawer.h"
#include "Primitive.h"
#include "Physics\Collision.h"
#include "CustomProperties.h"
#include "Shapes\Terrain.h"
#include "Rendering\StencilOutline.h"
#include "Builders\ShapesBuilder.h"
#include "Builders/LightBuilder.h"
#include "Managers/LightManager.h"
#include "SSAO/KernelSamplerGenerator.h"
#include "ThreadPool.h"
#include "RendererScreen.h"
#include "../ImGUI/imgui.h"

namespace AppEngine
{
	class OpenGLScene : public GameScene
	{
	public:
		OpenGLScene(GLFWwindow* window, ImVec2 size, ImVec2 position);
		int CreateScene() override;
		void SetSceneHovered(bool hovered);
		void ReinitializeScene(std::shared_ptr<Shape> shape);
		std::shared_ptr<FrameBuffer> RenderScene(ImVec2 size, ImVec2 position);
		void ClearScene();
		~OpenGLScene();
	private:

		Renderer* renderer;
		GLFWwindow* window;
		std::shared_ptr<Camera> cam;
		SkyBoxCube* skyboxShape;
		Terrain* terrainShape;
		Light* mainLight;
		std::vector<std::shared_ptr<Shape>> forwardShapes;
		std::vector<std::shared_ptr<Shape>> deferredShapes;
		std::vector<std::shared_ptr<Shape>> shadowShapes;
		std::vector<std::shared_ptr<Shape>> selectedShapes;


		/// temporary ssao texture
		Texture* ssaoNoiseTexture;
		std::vector<std::future<void>> futures;
		RendererScreen* screen;
		ImVec2 lastSize;
		ImVec2 lastPosition;
	};
}

