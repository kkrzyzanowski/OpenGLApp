#pragma once
#include "VertexBuffer.h"
#include <string>
class UniformBuffer
{
public: 
	UniformBuffer(unsigned int size);
	virtual ~UniformBuffer();
	void Bind() const;
	void UnBind() const;
	void LoadData(const void* data, size_t dataSize, size_t dataOffset);
private:
	unsigned int m_uniformBuffer;

};

