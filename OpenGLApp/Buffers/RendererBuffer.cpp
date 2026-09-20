#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include "RenderBuffer.h"
#include "..\Rendering\Renderer.h"
#include "..\Config.h"

namespace AppEngine
{
	RenderBuffer::RenderBuffer(glm::vec2 size) : size(size)
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

	void RenderBuffer::BindRenderTarget(unsigned int renderTargetRBO)
	{
		GLCall(glBindRenderbuffer(GL_RENDERBUFFER, renderTargetRBO));
	}

	void RenderBuffer::GenerateRenderBuffer()
	{
		GLCall(glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, SCREEN_WIDTH, SCREEN_HEIGHT));
	}


	void RenderBuffer::AttachDepthStencilFrameRenderBuffer()
	{
		GLCall(glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo));
	}

	void RenderBuffer::GenerateDepthRenderBuffer()
	{
		GLCall(glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, SCREEN_WIDTH, SCREEN_HEIGHT));
	}

	void RenderBuffer::GenerateDepthStencilRenderBuffer()
	{
		GLCall(glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, size.x, size.y));
	}


	void RenderBuffer::AttachDepthFrameRenderBuffer()
	{
		GLCall(glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rbo));
	}
	RenderBuffer::~RenderBuffer()
	{
	}
}