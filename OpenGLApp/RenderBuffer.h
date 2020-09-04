#pragma once


class RenderBuffer
{
public:
	RenderBuffer();
	void Bind();
	void UnBind();
	void GenerateRenderBuffer();
	void GenerateFrameRenderBuffer();
	inline unsigned int GetRenderBuffer() const { return rbo; };
	~RenderBuffer();
private:
	unsigned int rbo;
};

