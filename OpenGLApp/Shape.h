#pragma once
#include <GL\glew.h>
#include <GLFW/glfw3.h>
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"
 enum Shapes
{
	TRIANGLE = 9, RECTANGLE = 12
};
class Shape
{
public:
	Shape(Shapes shape);
	void CreateShape(const GLfloat* points, unsigned int* orderIndex);
	VertexArray* GetVertexArray();
	VertexBuffer* GetVertexBuffer();
	IndexBuffer* GetIndexBuffer();
	~Shape();
private:
	VertexArray* va;
	VertexBuffer*  vb;
	VertexBufferLayout* layout;
	IndexBuffer* ib;
	
};

