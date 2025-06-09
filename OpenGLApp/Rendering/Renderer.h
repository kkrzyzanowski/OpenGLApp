#pragma once
#include <iostream>
#include "..\glm\glm.hpp"
#include "..\glm\gtc\matrix_transform.hpp"
#include "..\glm\gtc\type_ptr.hpp"
#include "..\Managers\ShaderCompiler.h"
#include "..\Buffers\IndexBuffer.h"
#include "..\Buffers\VertexArray.h"
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
	void Draw(int count, GLenum mode) const;
	void DrawArrays(int count, GLenum mode) const;
	void DrawArrayInstances(int count, GLenum mode, unsigned int instancesCount ) const;
	void DrawLine(glm::vec3 start, glm::vec3 end);
	void Clear() const;
	void ClearColor() const;
	void ClearDepth() const;
	void ClearStencil() const;
};


