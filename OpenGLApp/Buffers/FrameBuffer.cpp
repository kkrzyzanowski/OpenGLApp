#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include "FrameBuffer.h"
#include "..\Shaders\ShaderClasses\ShaderTypeGenerator.h"
#include "..\Config.h"
#include "..\Rendering\Renderer.h"

//pos		//texture
float quad[] = {
		-1.0f,  1.0f,  0.0f, 1.0f,
		-1.0f, -1.0f,  0.0f, 0.0f,
		 1.0f, -1.0f,  1.0f, 0.0f,

		-1.0f,  1.0f,  0.0f, 1.0f,
		 1.0f, -1.0f,  1.0f, 0.0f,
		 1.0f,  1.0f,  1.0f, 1.0f };
unsigned int plane_indexes[] = { 0, 1, 2,
					3, 4, 5 };

unsigned int vertexSize = 6;
unsigned int indexSize = 6;
unsigned short bufferDataSize = 4;

FrameBuffer::FrameBuffer()
{
	GLCall(glGenFramebuffers(1, &fbo));
	bm = std::unique_ptr<BufferManager>(new BufferManager());
	sm = new ShaderManager();
	InitializeBufferScreenCoords();
	tm = new TextureManager();
}

FrameBuffer::FrameBuffer(FrameBufferBuilder& builder)
{
	GLCall(glGenFramebuffers(1, &fbo));
	bm = std::unique_ptr<BufferManager>(new BufferManager());
	sm = new ShaderManager();
	InitializeBufferScreenCoords();
	tm = new TextureManager();
	AddTexturesToBuffer(builder.textures, builder.type);
	AddShaders(builder.ShaderPaths);
	SetFunctionShader(builder.type);
	//InitializeShaders();
}

void FrameBuffer::Bind()
{
	GLCall(glBindFramebuffer(GL_FRAMEBUFFER, fbo));
}

void FrameBuffer::ReadBind()
{
	GLCall(glBindFramebuffer(GL_READ_FRAMEBUFFER, fbo));
}

void FrameBuffer::DrawBind()
{
	GLCall(glBindFramebuffer(GL_DRAW_FRAMEBUFFER, fbo));
}


void FrameBuffer::UnBind()
{
	GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
}


void FrameBuffer::GenerateTexture()
{
	tm->Textures.push_back(new Texture());
	tm->Textures[0]->CreateFrameBufferTexture();
}

void FrameBuffer::GenerateShadowTexture()
{
	tm->Textures.push_back(new Texture());
	tm->Textures[0]->CreateShadowMapTexture();
}

bool FrameBuffer::CheckFrameBuffer()
{
	bool status = (glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE);
	if (!status)
		std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
	return status;
}


void FrameBuffer::InitializeBufferScreenCoords()
{
	unsigned int bufferDataSizes[2] = { 2, 2 };
	bm->CreateBuffers(quad, plane_indexes, vertexSize, indexSize, bufferDataSizes, bufferDataSize);
}

void FrameBuffer::UnBindDrawBuffers()
{
	sc.DisableUse();
	bm->UnbindBuffers();
}

void FrameBuffer::BindDrawBuffers()
{
	sc.EnableUse();
	bm->BindBuffers();
}

void FrameBuffer::AddParams(ShaderParams param)
{
	params.push_back(param);
}

void FrameBuffer::UpdateParams(ShaderParams param, std::string& name)
{
}

void FrameBuffer::AddShaders(const std::vector<const char*>& paths)
{
	for (const char* path : paths)
	{
		sm->AddShader(path);
	}
}
void FrameBuffer::AddShaders(std::vector<Shader*>& shaders)
{
	sm->AddShaders(shaders);
}

std::vector<Shader*> FrameBuffer::GetFrameBufferShaders()
{
	return sm->shaders;
}


void FrameBuffer::InitializeShaders()
{
	if (sm->shaders.size() > 0)
	{
		sc.AddShadersToProgram(sm->shaders);
		sc.EnableUse();
		for (size_t i = 0; i < tm->Textures.size(); ++i)
			tm->Textures[i]->Bind();
		func(sm->shaders, sc.GetCurrentProgram(), params);
		for(size_t i = 0; i < tm->Textures.size(); ++i)
			tm->Textures[i]->UnBind();
		sc.DisableUse();
	}
}

void FrameBuffer::ExecuteShader()
{
	sc.EnableUse();
	func(sm->shaders, sc.GetCurrentProgram(), params);
}

void FrameBuffer::UpdateFrameBuffer()
{
	ExecuteShader();
}

void FrameBuffer::AfterUpdateFrameBuffer()
{
	sc.DisableUse();
	bm->UnbindBuffers();
	for(auto& tex: tm->Textures)
		tex->UnBind();
}

void FrameBuffer::AddTexturesToBuffer(std::vector<Texture*>& textures, FrameBufferType type)
{
	Bind();
	tm->AddTextures(textures);
	tm->InitializeTextures();
	DrawBuffers(type);
	UnBind();
}

void FrameBuffer::AddTexturesToBuffer(std::vector<Texture*>&& textures)
{
	tm->AddTextures(textures);
}

Texture* FrameBuffer::GetFramebufferTexture(unsigned int slot)
{
	return tm->Textures[slot];
}

std::vector<Texture*> FrameBuffer::GetFramebufferTextures()
{
	return tm->Textures;
}

IndexBuffer* FrameBuffer::GetIndexBuffer()
{
	return ib;
}

unsigned int FrameBuffer::GetFrameBuffer() const
{
	return fbo;
}

void FrameBuffer::DrawBuffers(unsigned short colorAtachhment)
{
	std::vector<GLenum> DrawBuffers(colorAtachhment + 1);
	for (int i = 0; i <= colorAtachhment; i++)
		DrawBuffers[i] = GL_COLOR_ATTACHMENT0 + i;
	glDrawBuffers(1, DrawBuffers.data());
}

void FrameBuffer::DrawBuffers(FrameBufferType type)
{
	if (type & (POSTPROCESSING | HDR | BLUR))
	{
		unsigned int textureSize = tm->Textures.size();
		std::vector<GLenum> DrawBuffers(textureSize);
		for (int i = 0; i < textureSize; i++)
			DrawBuffers[i] = GL_COLOR_ATTACHMENT0 + i;
		glDrawBuffers(textureSize, DrawBuffers.data());
	}
	else if(type & GBUFFER)
	{
		unsigned int textureSize = tm->Textures.size();
		std::vector<GLenum> DrawBuffers(textureSize);
		for (int i = 0; i < textureSize; i++)
			DrawBuffers[i] = GL_COLOR_ATTACHMENT0 + i;
		glDrawBuffers(textureSize, DrawBuffers.data());
	}
}

void FrameBuffer::SetFunctionShader(FrameBufferType type)
{
	switch (type)
	{
	case POSTPROCESSING:
	{
		func = ShaderTypeGenerator::PostProcesingShaderGenerator;
		break;
	}
	case MAIN:
	{
		func = ShaderTypeGenerator::PostProcesingShaderGenerator;
		break;
	}
	case BLUR:
	{
		func = ShaderTypeGenerator::HDRGaussianBlurShaderGenerator;
		break;
	}
	case HDR:
	{
		func = ShaderTypeGenerator::HDRShaderGenerator;
		break;
	}
	case DEPTHMAP:
	{
		break;
	}
	case GAUSSIAN_HORIZONTAL:
	{
		params.push_back(true);
		func = ShaderTypeGenerator::UpdateBloomShader;
		break;
	}
	case GAUSSIAN_VERTICAL:
	{
		params.push_back(false);
		func = ShaderTypeGenerator::UpdateBloomShader;
		break;
	}
	case GBUFFER:
	{
		func = ShaderTypeGenerator::DefferedShading;
		break;
	}
	case SSAO:
		func = ShaderTypeGenerator::SSAOShaderGenerator;
		break;

	case SSAO_LIGHTNING:
		func = ShaderTypeGenerator::UpdateSSAOShaderLightning;
		break;
	}
}

FrameBuffer::~FrameBuffer()
{
	delete tm;
	GLCall(glDeleteFramebuffers(1, &fbo));
}
