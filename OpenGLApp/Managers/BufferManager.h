#pragma once
#include <vector>
#include "..\Buffers\VertexBuffer.h"
#include "..\Buffers\IndexBuffer.h"
#include "..\Buffers\VertexArray.h"
#include "..\Buffers\VertexBufferLayout.h"
class BufferManager
{
public:
	void CreateBuffers(const GLfloat* points, unsigned int* orderIndex, unsigned int countVertices, unsigned int countIndexes, unsigned int* bufferDataSizes, unsigned int dataSize = 8);
	void CreateBuffersOnlyVertex(const GLfloat* points, unsigned int* orderIndex, unsigned int countVertices, unsigned int countIndexes);
	void CreateBuffers(const GLfloat* points, std::vector<int>& orderIndex, unsigned int countVertices, unsigned int countIndexes, unsigned int* bufferDataSizes, unsigned int dataSize = 8);
	void UnbindBuffers();
	void BindBuffers();
	VertexArray* GetVertexArray();
	VertexBuffer* GetVertexBuffer();
	IndexBuffer* GetIndexBuffer();
private:
	VertexArray* va;
	VertexBuffer* vb;
	VertexBufferLayout* layout;
	IndexBuffer* ib;
	void CreateVertexBufferLayoutData(VertexBufferLayout* layout, unsigned int dataSize);
	void CreateVertexBufferLayoutDataFromArray(VertexBufferLayout* layout, unsigned int dataSize, unsigned int* partDataSizes);
};

