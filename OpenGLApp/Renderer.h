#pragma once
#include <GL\glew.h>
#include <iostream>
#include "ShaderManager.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#define ASSERT(x) if((!x)) __debugbreak();
#define GLCall(x) GLClearError();\
x;\
ASSERT(GLLogCall(#x, __FILE__, __LINE__))
void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);

enum DrawMode
{
	ELEMENTS, ARRAYS
};
class Renderer
{
public:
	void Draw(int count) const;
	void DrawLine(glm::vec3 start, glm::vec3 end);
	void Clear() const;
};


