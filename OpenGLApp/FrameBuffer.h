#pragma once

#include <vector>
#include "RenderBuffer.h"
#include "Shader.h"
#include "VertexBufferLayout.h"

class FrameBuffer
{
public:
	FrameBuffer();
	void Bind();
	void UnBind();
	void GenerateTextureColorBuffer();
	void GenerateRenderBuffer();
	bool CheckFrameBuffer();
	void TurnOffFrameBufferElements();
	void TurnOnFrameBufferElements();
	void InitializePostProcessingShaders();
	void BindTexture();
	void UnBindTexture();
	IndexBuffer* GetIndexBuffer();
	~FrameBuffer();
private:
	void InitializePostProcessing();
	unsigned int texColorBuffer;
	unsigned int fbo;
	RenderBuffer* rbo;
	std::vector<Shader*> shaders;
	ShaderManager sm;
	VertexArray* va;
	VertexBuffer* vb;
	VertexBufferLayout* layout;
	IndexBuffer* ib;

};

