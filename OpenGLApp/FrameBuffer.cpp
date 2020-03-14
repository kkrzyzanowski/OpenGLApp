#include "FrameBuffer.h"
#include "ShaderTypeGenerator.h"
#include "Config.h"
#include "Renderer.h"
#include <GL\glew.h>
#include <GLFW/glfw3.h>

				//pos		//texture
float quad[] = {-1.0f, 1.0f, 0.0f, 1.0f,
				-1.0f, -1.0f, 0.0f, 0.0f,
				1.0f, -1.0f, 1.0f, 0.0f,
				1.0f, 1.0f, 1.0f, 1.0f};
float indexes[] = { 0, 1, 2,
					2, 3, 0 };
FrameBuffer::FrameBuffer()
{
	GLCall(glGenFramebuffers(1, &fbo));
	InitializePostProcessing();
}

void FrameBuffer::Bind()
{
	GLCall(glBindFramebuffer(GL_FRAMEBUFFER, fbo));
}


void FrameBuffer::UnBind()
{
	GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
}

void FrameBuffer::GenerateTextureColorBuffer()
{
	GLCall(glGenTextures(1, &texColorBuffer));
	GLCall(glBindTexture(GL_TEXTURE_2D, texColorBuffer));
	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, SCREEN_WIDTH, SCREEN_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
	//GLCall(glBindTexture(GL_TEXTURE_2D, 0));

	GLCall(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texColorBuffer, 0));
	
}

void FrameBuffer::GenerateRenderBuffer()
{
	rbo = new RenderBuffer();
	rbo->Bind();
	rbo->GenerateRenderBuffer();
	//rbo->UnBind();
	GLCall(glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rbo->GetRenderBuffer()));
}

bool FrameBuffer::CheckFrameBuffer()
{
	return (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) ? false : true;
}

void FrameBuffer::InitializePostProcessing()
{	
	va = new VertexArray();
	vb = new VertexBuffer(quad, sizeof(float) * 4 *(2+2));
	layout = new VertexBufferLayout();
	layout->Push<float>(2);
	layout->Push<float>(2);
	va->AddBuffer(*vb, *layout);
	ib = new IndexBuffer(indexes, 6);
	
}

void FrameBuffer::TurnOffFrameBufferElements()
{
	va->UnBind();
	vb->UnBind();
	ib->UnBind();
	sm.UnBind();
}

void FrameBuffer::TurnOnFrameBufferElements()
{
	va->Bind();
	vb->Bind();
	ib->Bind();
	sm.Bind();
}

void FrameBuffer::InitializePostProcessingShaders()
{
	shaders.push_back(new Shader("Shaders\\PostProcesingShader.vert"));
	shaders.push_back(new Shader("Shaders\\PostProcesingShader.frag"));
	sm.AddShadersToProgram(shaders);
	sm.Bind();
	BindTexture();
	ShaderTypeGenerator::PostProcesingShaderGenerator(shaders, sm.GetProgram());
	UnBindTexture();
}

void FrameBuffer::BindTexture()
{
	GLCall(glBindTexture(GL_TEXTURE_2D, texColorBuffer));
}

void FrameBuffer::UnBindTexture()
{
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}

IndexBuffer * FrameBuffer::GetIndexBuffer()
{
	return ib;
}


FrameBuffer::~FrameBuffer()
{
	GLCall(glDeleteFramebuffers(1, &fbo));
}
