#pragma once
#include <vector>
#include <map>
#include <memory>
#include "..\Enums.h"
#include "..\glm\glm.hpp"

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
	//static void CopyFRBuffer(FrameBufferType type, FrameBuffer& other);
	static void InitializeFrameBuffers();

	static void PassShadowDataToShader(std::shared_ptr<Shape> shape);

	static void SetTextureUnactive();

	static void SetTextureActive();

	static void AddKernelSamplesToSSAOBuffer(std::vector<glm::vec3>& samples);

	static std::map<FrameBufferType, FRBufferContainer> FRbuffer_container;
	~FrameBufferManager();
};


