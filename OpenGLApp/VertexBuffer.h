#pragma once
class VertexBuffer
{
public:
	VertexBuffer(const void* data, unsigned int size);
	virtual ~VertexBuffer();
	 void Bind() const;
	 void UnBind() const;
private:
	unsigned int m_vertexBuffer;
};

