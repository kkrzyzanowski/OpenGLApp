#include "RenderBuffer.h"
#include "Renderer.h"
#include <GL\glew.h>
#include <GLFW/glfw3.h>
#include "Config.h"

RenderBuffer::RenderBuffer()
{
	GLCall(glGenRenderbuffers(1, &rbo));
}

void RenderBuffer::Bind()
{
	GLCall(glBindRenderbuffer(GL_RENDERBUFFER, rbo));
}

void RenderBuffer::UnBind()
{
	GLCall(glBindRenderbuffer(GL_RENDERBUFFER, 0));
}

void RenderBuffer::GenerateRenderBuffer()
{
	GLCall(glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 1280, 720));
}


void RenderBuffer::GenerateFrameRenderBuffer()
{
	GLCall(glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo));
}

RenderBuffer::~RenderBuffer()
{
}
