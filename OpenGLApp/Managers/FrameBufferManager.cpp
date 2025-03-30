#include "FrameBufferManager.h"
#include "..\Buffers\RenderBuffer.h";
#include "..\Buffers\FrameBuffer.h";
#include "..\Shapes\Shape.h";

std::map<FrameBufferType, FRBufferContainer> FrameBufferManager:: FRbuffer_container;
FrameBufferManager::FrameBufferManager()
{
}

void FrameBufferManager::CreateFRBuffer(FrameBufferType type, std::shared_ptr<FrameBuffer> fb)
{
	FRbuffer_container.insert({ type, { fb, std::make_shared<RenderBuffer>() } });
}

void FrameBufferManager::InitializeFrameBuffers()
{
	for (auto& [key, val] : FRbuffer_container)
	{
		switch (key)
		{
		case POSTPROCESSING:
		{
			val.frameBuffer->Bind();
			val.rendererBuffer->Bind();
			val.rendererBuffer->GenerateDepthRenderBuffer();
			val.rendererBuffer->UnBind();
			val.rendererBuffer->GenerateDepthFrameRenderBuffer();
			//val.frameBuffer->UnBind();
			break;
		}
		case HDR:
		{
			val.frameBuffer->Bind();
			val.rendererBuffer->Bind();
			val.rendererBuffer->GenerateDepthRenderBuffer();
			val.rendererBuffer->UnBind();
			val.rendererBuffer->GenerateDepthFrameRenderBuffer();
			break;
		}
		case DEPTHMAP:
		{
			break;
		}
		}
	}
}

void FrameBufferManager::PassShadowDataToShader(std::shared_ptr<Shape> shape)
{
	for (auto& [key, val] : FRbuffer_container)
	{
		if (key == DEPTHMAP && shape->IsShadowTurnOn())
		{
			shape->tm.AddTexture(val.frameBuffer->GetFramebufferTexture());
		}
	}
}

void FrameBufferManager::SetTextureUnactive()
{
	FRbuffer_container[DEPTHMAP].frameBuffer->GetFramebufferTexture()->SetActive(false);
}

void FrameBufferManager::SetTextureActive()
{
	FRbuffer_container[DEPTHMAP].frameBuffer->GetFramebufferTexture()->SetActive(true);
}

FrameBufferManager::~FrameBufferManager()
{
}
