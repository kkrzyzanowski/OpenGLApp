#include "UniformBuffer.h"
#include "..\Rendering\Renderer.h"
#include <cstddef>

UniformBuffer::UniformBuffer(unsigned int size)
{
	glGenBuffers(1, &m_uniformBuffer);
	Bind();
	glBufferData(GL_UNIFORM_BUFFER, size, NULL, GL_STATIC_DRAW);
	UnBind();
	GLCall(glBindBufferRange(GL_UNIFORM_BUFFER, 0, m_uniformBuffer, 0, size));
}

UniformBuffer::~UniformBuffer()
{
}

void UniformBuffer::Bind() const
{
	GLCall(glBindBuffer(GL_UNIFORM_BUFFER, m_uniformBuffer));
}

void UniformBuffer::UnBind() const
{
	GLCall(glBindBuffer(GL_UNIFORM_BUFFER, 0));
}

void UniformBuffer::LoadData(const void* data, size_t dataSize, size_t dataOffset)
{
	GLCall(glBufferSubData(GL_UNIFORM_BUFFER, dataOffset, dataSize, data));
}



