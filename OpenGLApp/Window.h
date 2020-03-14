#pragma once
#include <GL\glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Shape.h"
#include "Shader.h"
#include "ShapeManager.h"
class Window
{
public:
	Window();
	int CreateWindow();
	~Window();
private:
	
	Renderer *renderer;
};

