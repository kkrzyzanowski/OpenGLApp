#include "FrameBuffer.h"
#include "ShaderTypeGenerator.h"
#include "Config.h"
#include "Renderer.h"
#include <GL\glew.h>
#include <GLFW/glfw3.h>

				//pos		//texture
float quad[] = { 
		-1.0f,  1.0f,  0.0f, 1.0f,
		-1.0f, -1.0f,  0.0f, 0.0f,
		 1.0f, -1.0f,  1.0f, 0.0f,

		-1.0f,  1.0f,  0.0f, 1.0f,
		 1.0f, -1.0f,  1.0f, 0.0f,
		 1.0f,  1.0f,  1.0f, 1.0f };
float indexes[] = { 0, 1, 2,
					3, 4, 5 };
FrameBuffer::FrameBuffer()
{
	GLCall(glGenFramebuffers(1, &fbo));
	InitializeFrameBufferCoords();
}

void FrameBuffer::Bind()
{
	GLCall(glBindFramebuffer(GL_FRAMEBUFFER, fbo));
}


void FrameBuffer::UnBind()
{
	GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
}


void FrameBuffer::GenerateTexture()
{
	fbTexture = new Texture();
	fbTexture->CreateFrameBufferTexture();
}

bool FrameBuffer::CheckFrameBuffer()
{
	bool status = (glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE);
	return status;
}

void FrameBuffer::InitializeFrameBufferCoords()
{	
	va = new VertexArray();
	unsigned int vaCount = sizeof(float) * 6 * (2 + 2);
	vb = new VertexBuffer(quad, vaCount);
	layout = new VertexBufferLayout();
	layout->Push<float>(2);
	layout->Push<float>(2);
	va->AddBuffer(*vb, *layout);
	ib = new IndexBuffer(indexes, 6);
	
}

void FrameBuffer::TurnOffFrameBufferElements()
{
	sm.UnBind();
	va->UnBind();
	vb->UnBind();
	ib->UnBind();
}

void FrameBuffer::TurnOnFrameBufferElements()
{
	sm.Bind();
	va->Bind();
	vb->Bind();
	ib->Bind();
}

void FrameBuffer::InitializePostProcessingShaders()
{
	shaders.push_back(new Shader("Shaders\\PostProcesingShader.vert"));
	shaders.push_back(new Shader("Shaders\\PostProcesingShader.frag"));
	sm.AddShadersToProgram(shaders);
	sm.Bind();
	fbTexture->Bind();
	ShaderTypeGenerator::PostProcesingShaderGenerator(shaders, sm.GetProgram());
	//fbTexture->UnBind();
	//sm.UnBind();
}


Texture* FrameBuffer::GetFramebufferTexture()
{
	return fbTexture;
}

IndexBuffer * FrameBuffer::GetIndexBuffer()
{
	return ib;
}


FrameBuffer::~FrameBuffer()
{
	GLCall(glDeleteFramebuffers(1, &fbo));
}
