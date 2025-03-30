#pragma once
#include <vector>
#include "..\Buffers\IndexBuffer.h"
#include "..\Buffers\VertexArray.h"
#include "..\Buffers\UniformBuffer.h"
#include "..\Buffers\VertexBufferLayout.h"
class VertexManager
{
public:
	void CreateShape3D(const GLfloat* points, unsigned int* orderIndex, unsigned int countVertices, unsigned int countIndexes);
	void CreateShape2D(const GLfloat* points, unsigned int* orderIndex, unsigned int countVertices, unsigned int countIndexes);
	void CreateShape(const GLfloat* points, std::vector<int>& orderIndex, unsigned int countVertices, unsigned int countIndexes);
	VertexArray* GetVertexArray();
	VertexBuffer* GetVertexBuffer();
	IndexBuffer* GetIndexBuffer();
	void UnbindBufferObjects();

	static UniformBuffer* ub;
private:
	VertexArray* va;
	VertexBuffer* vb;
	VertexBufferLayout* layout;
	IndexBuffer* ib;
};

