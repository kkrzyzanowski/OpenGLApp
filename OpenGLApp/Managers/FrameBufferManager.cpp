#include "FrameBufferManager.h"
#include "..\Buffers\RenderBuffer.h";
#include "..\Buffers\FrameBuffer.h";
#include "..\Shapes\Shape.h";

namespace AppEngine
{
	std::map<FrameBufferType, FRBufferContainer> FrameBufferManager::FRbuffer_container;
	FrameBufferManager::FrameBufferManager()
	{
		FRbuffer_container[MAIN] = { std::make_shared<FrameBuffer>(), nullptr };
	}

	void FrameBufferManager::CreateFRBuffer(FrameBufferType type, std::shared_ptr<FrameBuffer> fb, std::shared_ptr<RenderBuffer> rb)
	{
		if (rb == nullptr)
			rb = std::make_shared<RenderBuffer>(fb->GetSize());
		FRbuffer_container.insert({ type, { fb, rb } });
	}

	//void FrameBufferManager::CopyFRBuffer(FrameBufferType type, FrameBuffer& other)
	//{
	//	FRbuffer_container.insert({ type, { std::make_shared<FrameBuffer>(other), std::make_shared<RenderBuffer>()}});
	//}

	void FrameBufferManager::InitializeFrameBuffers(unsigned int renderTargetFBO)
	{
		constexpr int ANY_OF_INTEREST = MAIN | POSTPROCESSING | BLUR | HDR;
		constexpr int SHADOW = DEPTHMAP;
		for (auto& [key, val] : FRbuffer_container)
		{
			if (key & ANY_OF_INTEREST)
			{
				val.frameBuffer->Bind();
				val.rendererBuffer->Bind();
				val.rendererBuffer->GenerateDepthStencilRenderBuffer();
				val.rendererBuffer->UnBind();
				val.rendererBuffer->AttachDepthStencilFrameRenderBuffer();
				//val.frameBuffer->UnBind(renderTargetFBO);
			}
			if (key & SHADOW)
			{
				val.frameBuffer->Bind();
				val.rendererBuffer->Bind();
				val.rendererBuffer->GenerateDepthRenderBuffer();
				val.rendererBuffer->UnBind();
				val.rendererBuffer->AttachDepthFrameRenderBuffer();
			}
			if (key & GBUFFER)
			{
				val.frameBuffer->Bind();
				val.rendererBuffer->Bind();
				val.rendererBuffer->GenerateDepthStencilRenderBuffer();
				val.rendererBuffer->UnBind();
				val.rendererBuffer->AttachDepthStencilFrameRenderBuffer();
				//val.frameBuffer->UnBind(renderTargetFBO);
			}
		}
	}

	void FrameBufferManager::PassShadowDataToShader(std::shared_ptr<Shape> shape)
	{
		for (auto& [key, val] : FRbuffer_container)
		{
			if (SHADOW && (key & DEPTHMAP) && shape->IsShadowTurnOn())
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

	void FrameBufferManager::AddKernelSamplesToSSAOBuffer(std::vector<glm::vec3>& samples)
	{
		if (FRBufferContainer* ssaoBuffer = &FRbuffer_container[SSAO]; ssaoBuffer != nullptr)
			ssaoBuffer->frameBuffer->AddParams(samples);
	}

	FrameBufferManager::~FrameBufferManager()
	{
	}
}