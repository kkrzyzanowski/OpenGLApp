#pragma once

#include <vector>
#include <functional>
#include "RenderBuffer.h"
#include "..\Shaders\ShaderClasses\Shader.h"
#include "..\Buffers\VertexBufferLayout.h"
#include "..\TextureObjects\Texture.h"
#include "..\Managers\TextureManager.h"

#include "../Managers/BufferManager.h"
#include "../Shaders/ShaderClasses/ShaderTypeGenerator.h"
#include "../Shaders/ShaderClasses/ShaderManager.h"
#include "../DataStructures.h"
#include "../Builders/FrameBufferBuilder.h"

class FrameBuffer
{
public:
	FrameBuffer();
	FrameBuffer(FrameBufferBuilder& builder);
	void Bind();
	void ReadBind();
	void DrawBind();
	static void UnBind();
	void GenerateTexture();
	void GenerateShadowTexture();
	bool CheckFrameBuffer();
	void TurnOffFrameBufferElements();
	void TurnOnFrameBufferElements();
	void InitializeShaders(unsigned short textureSlot = 0);
	void InitializePostProcessingShaders();
	void AddTexturesToBuffer(std::vector<Texture*>& textures, FrameBufferType type);
	void AddTexturesToBuffer(std::vector<Texture*>&& textures);
	void InitializeHDRShaders();

	void InitializeGaussianBlurShaders();

	void UpdateGaussianBlurShaders(bool horizontal);
	void InitializeFrameBufferShader(const std::string& vertexPath, const std::string& fragmentPath, std::function<void(std::vector<Shader*>&, unsigned int)> shaderGeneratorFunc);
	void InitializeFrameBufferShader(const char* vertexPath, const char* fragmentPath, std::function<void(std::vector<Shader*>&, unsigned int)> shaderGeneratorFunc);

	Texture* GetFramebufferTexture(unsigned int slot = 0);
	std::vector<Texture*> GetFramebufferTextures();
	IndexBuffer* GetIndexBuffer();
	unsigned int GetFrameBuffer() const;
	void DrawBuffers(unsigned short colorAtachhment);
	void DrawBuffers(FrameBufferType type);
	void SetFunctionShader(FrameBufferType type);
	void AddParams(ShaderParams param);
	void UpdateParams(ShaderParams param, std::string& name);
	void AddShaders(const std::vector<const char*>& paths);
	void AddShaders(std::vector<Shader*>& shaders);
	std::vector<Shader*> GetFrameBufferShaders();

	~FrameBuffer();
private:
	void InitializeBufferScreenCoords();
	unsigned int texColorBuffer;
	unsigned int fbo;
	unsigned int ftbo;

	RenderBuffer* rbo;
	ShaderManager* sm;
	ShaderCompiler sc;
	VertexArray* va;
	VertexBuffer* vb;
	VertexBufferLayout* layout;
	IndexBuffer* ib;
	std::unique_ptr<BufferManager> bm;
	std::vector<ShaderParams> params;
	ShaderFunction func;
	FrameBufferType type;
	TextureManager* tm;

};

