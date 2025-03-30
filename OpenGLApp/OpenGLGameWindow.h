#pragma once
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <iostream>
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
#include "Managers\ShapeManager.h"
#include "Camera\RayDrawer.h"
#include "Primitive.h"
#include "Physics\Collision.h"
#include "CustomProperties.h"
#include "Shapes\Terrain.h"
#include "Rendering\StencilOutline.h"
#include "Builders\ShapesBuilder.h"
#include "Builders/LightBuilder.h"
#include "Managers/LightManager.h"
class OpenGLGameWindow: public GameWindow
{
public:
	OpenGLGameWindow();
	int CreateWindow() override;
	~OpenGLGameWindow();
private:
	
	Renderer *renderer;
};


