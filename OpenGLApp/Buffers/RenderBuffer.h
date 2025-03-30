#pragma once


class RenderBuffer
{
public:
	RenderBuffer();
	void Bind();
	void UnBind();
	void GenerateRenderBuffer();
	void GenerateFrameRenderBuffer();
	void GenerateDepthRenderBuffer();
	inline unsigned int GetRenderBuffer() const { return rbo; };
	void GenerateDepthFrameRenderBuffer();
	~RenderBuffer();
private:
	unsigned int rbo;
};

