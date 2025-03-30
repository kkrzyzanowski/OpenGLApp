#pragma once
class IndexBuffer
{
public:
	IndexBuffer(const void* data, unsigned int count);
	 ~IndexBuffer();
	void Bind() const;
	void UnBind() const;
	inline unsigned int GetCount() const { return m_count; }
private:
	unsigned int m_IndexBuffer;
	unsigned int m_count;

};

