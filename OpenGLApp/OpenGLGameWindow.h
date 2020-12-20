#pragma once
#include <GL\glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "GameWindow.h"
#include "Shape.h"
#include "Shader.h"
#include "ShapeManager.h"
class OpenGLGameWindow: public GameWindow
{
public:
	OpenGLGameWindow();
	int CreateWindow() override;
	~OpenGLGameWindow();
private:
	
	Renderer *renderer;
};


