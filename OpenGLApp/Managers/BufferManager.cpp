#include "BufferManager.h"
void BufferManager::CreateBuffers(const GLfloat* points, unsigned int* orderIndex, unsigned int countVertices, unsigned int countIndexes, unsigned int* bufferDataSizes, unsigned int dataSize)
{
	va = new VertexArray();
	vb = new VertexBuffer(points, sizeof(float) * countVertices * (dataSize));
	layout = new VertexBufferLayout();
	CreateVertexBufferLayoutDataFromArray(layout, dataSize, bufferDataSizes);
	va->AddBuffer(*vb, *layout);
	ib = new IndexBuffer(orderIndex, countIndexes); //indexes count
}

void BufferManager::CreateBuffersOnlyVertex(const GLfloat* points, unsigned int* orderIndex, unsigned int countVertices, unsigned int countIndexes)
{
	va = new VertexArray();
	vb = new VertexBuffer(points, sizeof(float) * countVertices * (3));
	layout = new VertexBufferLayout();
	layout->Push<float>(3); // vertexes
	va->AddBuffer(*vb, *layout);
	ib = new IndexBuffer(orderIndex, countIndexes); //indexes count
}

void BufferManager::CreateBuffers(const GLfloat* points, std::vector<int>& orderIndex, unsigned int countVertices, unsigned int countIndexes, unsigned int* bufferDataSizes, unsigned int dataSize)
{
	va = new VertexArray();
	vb = new VertexBuffer(points, sizeof(float) * countVertices * (dataSize));
	layout = new VertexBufferLayout();
	CreateVertexBufferLayoutDataFromArray(layout, dataSize, bufferDataSizes);
	va->AddBuffer(*vb, *layout);
	ib = new IndexBuffer(static_cast<void*>(orderIndex.data()), countIndexes); //indexes count
}

void BufferManager::UnbindBuffers()
{
	va->UnBind();
	vb->UnBind();
	ib->UnBind();
}

void BufferManager::BindBuffers()
{
	va->Bind();
	vb->Bind();
	ib->Bind();
}

VertexArray* BufferManager::GetVertexArray()
{
	return va;
}

VertexBuffer* BufferManager::GetVertexBuffer()
{
	return vb;
}

IndexBuffer* BufferManager::GetIndexBuffer()
{
	return ib;
}

void BufferManager::CreateVertexBufferLayoutData(VertexBufferLayout* layout, unsigned int dataSize)
{
	for (int step = 0; dataSize > 0; dataSize -= 3, ++step)
	{
		if (step == 1)
		{
			++dataSize;
			layout->Push<float>(2);
		}
		else
			layout->Push<float>(3);
	}
}

void BufferManager::CreateVertexBufferLayoutDataFromArray(VertexBufferLayout* layout, unsigned int dataSize, unsigned int* partDataSizes)
{
	unsigned int i = 0;
	while (dataSize > 0)
	{
		layout->Push<float>(partDataSizes[i]);
		dataSize -= partDataSizes[i];
		++i;
	}
}