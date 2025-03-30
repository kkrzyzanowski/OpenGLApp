#pragma once
#include <vector>
#include <map>
#include <memory>
#include "..\ShapeType.h"

class FrameBuffer;
class RenderBuffer;
class Shape;

struct FRBufferContainer
{
	std::shared_ptr<FrameBuffer> frameBuffer;
	std::shared_ptr<RenderBuffer> rendererBuffer;
};


static class FrameBufferManager
{
public:
	FrameBufferManager();
	static void CreateFRBuffer(FrameBufferType type, std::shared_ptr<FrameBuffer> fb);
	static void InitializeFrameBuffers();

	static void PassShadowDataToShader(std::shared_ptr<Shape> shape);

	static void SetTextureUnactive();

	static void SetTextureActive();

	static std::map<FrameBufferType, FRBufferContainer> FRbuffer_container;
	~FrameBufferManager();
};


