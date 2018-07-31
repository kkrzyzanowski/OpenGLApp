#include "IndexBuffer.h"
#include "GL\glew.h"
#include "Renderer.h"

IndexBuffer::IndexBuffer(const void* data, unsigned int count) 
: m_count(count)
{
	ASSERT(sizeof(unsigned int) == sizeof(GLuint));

	GLCall(glGenBuffers(1, &m_IndexBuffer));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer));
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));
}


IndexBuffer::~IndexBuffer()
{
	GLCall(glDeleteBuffers(1, &m_IndexBuffer));
}

void IndexBuffer::Bind() const
{
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer));
}

void IndexBuffer::UnBind() const
{
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}
