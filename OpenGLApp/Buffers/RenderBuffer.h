#pragma once
#include "..\glm\glm.hpp"

class RenderBuffer
{
public:
	RenderBuffer() = default;
	RenderBuffer(glm::vec2 size);
	void Bind();
	void UnBind();
	void BindRenderTarget(unsigned int renderTargetRBO);
	void GenerateRenderBuffer();
	void AttachDepthStencilFrameRenderBuffer();
	void GenerateDepthRenderBuffer();
	void GenerateDepthStencilRenderBuffer();
	inline unsigned int GetRenderBuffer() const { return rbo; };
	void AttachDepthFrameRenderBuffer();
	~RenderBuffer();
private:
	unsigned int rbo;
	glm::vec2 size;
};

