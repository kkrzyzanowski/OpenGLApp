#pragma once

#include <vector>
#include "RenderBuffer.h"
#include "Shader.h"
#include "VertexBufferLayout.h"
#include "Texture.h"

class FrameBuffer
{
public:
	FrameBuffer();
	void Bind();
	void UnBind();
	void GenerateRenderBuffer(RenderBuffer* rbo);
	void GenerateTexture();
	bool CheckFrameBuffer();
	void TurnOffFrameBufferElements();
	void TurnOnFrameBufferElements();
	void InitializePostProcessingShaders();

	Texture* GetFramebufferTexture();
	IndexBuffer* GetIndexBuffer();
	~FrameBuffer();
private:
	void InitializeFrameBufferCoords();
	unsigned int texColorBuffer;
	unsigned int fbo;
	unsigned int ftbo;

	Texture* fbTexture;
	RenderBuffer* rbo;
	std::vector<Shader*> shaders;
	ShaderManager sm;
	VertexArray* va;
	VertexBuffer* vb;
	VertexBufferLayout* layout;
	IndexBuffer* ib;

};

