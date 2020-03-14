#pragma once


class RenderBuffer
{
public:
	RenderBuffer();
	void Bind();
	void UnBind();
	void GenerateRenderBuffer();
	unsigned int GetRenderBuffer();
	~RenderBuffer();
private:
	unsigned int rbo;
};

