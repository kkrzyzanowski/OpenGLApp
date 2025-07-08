#pragma once


class RenderBuffer
{
public:
	RenderBuffer();
	void Bind();
	void UnBind();
	void GenerateRenderBuffer();
	void AttachStencilDepthFrameRenderBuffer();
	void GenerateDepthRenderBuffer();
	void GenerateDepthStencilRenderBuffer();
	inline unsigned int GetRenderBuffer() const { return rbo; };
	void AttachDepthFrameRenderBuffer();
	~RenderBuffer();
private:
	unsigned int rbo;
};

