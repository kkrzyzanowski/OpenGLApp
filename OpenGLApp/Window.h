#pragma once
#include <GL\glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Shape.h"
#include "Shader.h"
class Window
{
public:
	Window();
	int CreateWindow();
	virtual ~Window();
private:
	Shape * shape;
	Renderer *renderer;
};

