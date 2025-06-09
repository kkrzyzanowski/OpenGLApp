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
	InitializeShaders();
}

//FrameBuffer::FrameBuffer(FrameBuffer& other, FrameBufferBuilder& builder)
//{
//	GLCall(glGenFramebuffers(1, &fbo));
//	bm = std::unique_ptr<BufferManager>(new BufferManager());
//	sc = other.sc;
//	sm = other.sm;
//	tm = new TextureManager();
//	AddTexturesToBuffer(builder.textures, builder.type);
//}

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

void FrameBuffer::TurnOffFrameBufferElements()
{
	sc.DisableUse();
	bm->UnbindBuffers();
}

void FrameBuffer::TurnOnFrameBufferElements()
{
	sc.EnableUse();
	bm->BindBuffers();
}

void FrameBuffer::AddParams(ShaderParams param)
{
	params.push_back(param);
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


void FrameBuffer::InitializeShaders(unsigned short textureSlot)
{
	if (sm->shaders.size() > 0)
	{
		sc.AddShadersToProgram(sm->shaders);
		sc.EnableUse();
		tm->Textures[textureSlot]->Bind();
		func(sm->shaders, sc.GetCurrentProgram(), params);
		tm->Textures[textureSlot]->UnBind();
		sc.DisableUse();
	}
}

void FrameBuffer::InitializePostProcessingShaders()
{
	/*shaders.push_back(new Shader("Shaders\\PostProcesingShader.vert"));
	shaders.push_back(new Shader("Shaders\\PostProcesingShader.frag"));
	sc.AddShadersToProgram(shaders);
	sc.EnableUse();
	tm->Textures[0]->Bind();
	ShaderTypeGenerator::PostProcesingShaderGenerator(shaders, sc.GetDefaultProgram());*/
	//fbTexture->UnBind();
	//sm.UnBind();
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

void FrameBuffer::InitializeHDRShaders()
{
	/*shaders.push_back(new Shader("Shaders\\HDRGaussianBlurShader.vert"));
	shaders.push_back(new Shader("Shaders\\HDRGaussianBlurShader.frag"));
	sc.AddShadersToProgram(shaders);
	sc.EnableUse();
	tm->Textures[0]->Bind();
	ShaderTypeGenerator::HDRGaussianBlurShaderGenerator(shaders, sc.GetDefaultProgram());
	tm->Textures[0]->UnBind();*/
	//sm.UnBind();
}

void FrameBuffer::InitializeGaussianBlurShaders()
{
	/*shaders.push_back(new Shader("Shaders\\GaussianBlurShader.vert"));
	shaders.push_back(new Shader("Shaders\\GaussianBlurShader.frag"));
	sc.AddShadersToProgram(shaders);
	sc.EnableUse();
	tm->Textures[0]->Bind();
	ShaderTypeGenerator::UpdateBloomShader(shaders, true, sc.GetDefaultProgram());
	tm->Textures[0]->UnBind();
	sc.DisableUse();*/
}

void FrameBuffer::UpdateGaussianBlurShaders(bool horizontal)
{
	//sc.EnableUse();
	//tm->Textures[0]->Bind();
	//ShaderTypeGenerator::UpdateBloomShader(shaders, 0, sc.GetDefaultProgram());
	//tm->Textures[0]->UnBind();
	//sc.DisableUse();
}

void FrameBuffer::InitializeFrameBufferShader(const std::string& vertexPath, const std::string& fragmentPath, std::function<void(std::vector<Shader*>&, unsigned int)> shaderGeneratorFunc)
{
	/*shaders.push_back(new Shader(vertexPath));
	shaders.push_back(new Shader(fragmentPath));
	sc.AddShadersToProgram(shaders);
	sc.EnableUse();
	tm->Textures[0]->Bind();
	shaderGeneratorFunc(shaders, sc.GetDefaultProgram());
	tm->Textures[0]->UnBind();
	sc.DisableUse();*/
}

void FrameBuffer::InitializeFrameBufferShader(const char* vertexPath, const char* fragmentPath, std::function<void(std::vector<Shader*>&, unsigned int)> shaderGeneratorFunc)
{
	/*shaders.push_back(new Shader(vertexPath));
	shaders.push_back(new Shader(fragmentPath));
	sc.AddShadersToProgram(shaders);
	sc.EnableUse();
	tm->Textures[0]->Bind();
	shaderGeneratorFunc(shaders, sc.GetDefaultProgram());
	tm->Textures[0]->UnBind();
	sc.DisableUse();*/
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
	case GAUUSIAN_HORIZONTAL:
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
		tm->Textures.push_back(new Texture(0, 0, GL_FLOAT, TextureMode::FRAMEBUFFER));
		tm->Textures.push_back(new Texture(1, 1, GL_FLOAT, TextureMode::FRAMEBUFFER));
		tm->Textures.push_back(new Texture(2, 2, GL_UNSIGNED_BYTE, TextureMode::FRAMEBUFFER));
		for (Texture* tex : tm->Textures)
			tex->CreateTextureForFrameBuffer();
		//DrawBuffers();
		func = ShaderTypeGenerator::PassLightMatrixData;
	}

	}
}
FrameBuffer::~FrameBuffer()
{
	delete tm;
	GLCall(glDeleteFramebuffers(1, &fbo));
}
