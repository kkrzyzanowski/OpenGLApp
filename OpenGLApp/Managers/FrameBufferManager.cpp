#include "FrameBufferManager.h"
#include "..\Buffers\RenderBuffer.h";
#include "..\Buffers\FrameBuffer.h";
#include "..\Shapes\Shape.h";

std::map<FrameBufferType, FRBufferContainer> FrameBufferManager:: FRbuffer_container;
FrameBufferManager::FrameBufferManager()
{
	FRbuffer_container[MAIN] = {std::make_shared<FrameBuffer>(), nullptr};
}

void FrameBufferManager::CreateFRBuffer(FrameBufferType type, std::shared_ptr<FrameBuffer> fb)
{
	FRbuffer_container.insert({ type, { fb, std::make_shared<RenderBuffer>() } });
}

//void FrameBufferManager::CopyFRBuffer(FrameBufferType type, FrameBuffer& other)
//{
//	FRbuffer_container.insert({ type, { std::make_shared<FrameBuffer>(other), std::make_shared<RenderBuffer>()}});
//}

void FrameBufferManager::InitializeFrameBuffers()
{
	constexpr int ANY_OF_INTEREST = POSTPROCESSING | BLUR | HDR | DEPTHMAP;
	for (auto& [key, val] : FRbuffer_container)
	{
		if (key & ANY_OF_INTEREST)
		{
			val.frameBuffer->Bind();
			val.rendererBuffer->Bind();
			val.rendererBuffer->GenerateDepthStencilRenderBuffer();
			val.rendererBuffer->UnBind();
			val.rendererBuffer->AttachDepthFrameRenderBuffer();
			//val.frameBuffer->UnBind();
		}
	}
}

void FrameBufferManager::PassShadowDataToShader(std::shared_ptr<Shape> shape)  
{  
    for (auto& [key, val] : FRbuffer_container)  
    {  
        if ((key & DEPTHMAP) && shape->IsShadowTurnOn())  
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
