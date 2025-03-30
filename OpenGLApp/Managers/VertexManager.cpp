#include "VertexManager.h"

void VertexManager::CreateShape3D(const GLfloat* points, unsigned int* orderIndex, unsigned int countVertices, unsigned int countIndexes)
{
	va = new VertexArray();
	vb = new VertexBuffer(points, sizeof(float) * countVertices * (3 + 2 + 3));
	layout = new VertexBufferLayout();
	layout->Push<float>(3); // vertexes
	layout->Push<float>(2); //textcoorssd
	layout->Push<float>(3); // normals
	va->AddBuffer(*vb, *layout);
	ib = new IndexBuffer(orderIndex, countIndexes);
}

void VertexManager::CreateShape2D(const GLfloat* points, unsigned int* orderIndex, unsigned int countVertices, unsigned int countIndexes)
{
	va = new VertexArray();
	vb = new VertexBuffer(points, sizeof(float) * countVertices * (3 + 2 + 3));
	layout = new VertexBufferLayout();
	layout->Push<float>(2); // vertexes
	layout->Push<float>(2); //textcoorssd
	layout->Push<float>(2); // normals
	va->AddBuffer(*vb, *layout);
	ib = new IndexBuffer(orderIndex, countIndexes);
}

void VertexManager::CreateShape(const GLfloat* points, std::vector<int>& orderIndex, unsigned int countVertices, unsigned int countIndexes)
{
	va = new VertexArray();
	vb = new VertexBuffer(points, sizeof(float) * countVertices * (3 + 2 + 3));
	layout = new VertexBufferLayout();
	layout->Push<float>(3); // vertexes
	layout->Push<float>(2); //textcoorssd
	layout->Push<float>(3); // normals
	va->AddBuffer(*vb, *layout);
	ib = new IndexBuffer(static_cast<void*>(orderIndex.data()), countIndexes);
}

VertexArray* VertexManager::GetVertexArray()
{
	return va;
}

VertexBuffer* VertexManager::GetVertexBuffer()
{
	return vb;
}

IndexBuffer* VertexManager::GetIndexBuffer()
{
	return ib;
}

void VertexManager::UnbindBufferObjects()
{
	va->UnBind();
	vb->UnBind();
	ib->UnBind();
}
