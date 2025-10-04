#pragma once
#include <memory>
#include "Managers/BufferManager.h"
#include "Shaders/ShaderClasses/ShaderManager.h"
#include "Shapes/VerticesCreator.h"
#include "Managers/TextureManager.h"
#include "DataStructures.h"
class RendererScreen
{
public:
	RendererScreen();
	RendererScreen(Paths paths, ShaderProperties props);
	void InitializeBufferScreenCoords();
	void AddTexturesToScreen(std::vector<const char*> paths);
	void AddShadersToScreen(std::vector<const char*> paths);
	void AddParam(ShaderParams& param);
	void AddParams(std::vector<ShaderParams>& params);
	void UpdateParam(unsigned short index, ShaderParams& value);
	void SetFunctionForShaders(ShaderProperties props);
	void Update();
	void AfterUpdate();
	~RendererScreen();
private:
	std::unique_ptr<BufferManager> bufferManager;
	std::unique_ptr<TextureManager> textureManager;
	std::unique_ptr<ShaderManager> shaderManager;
	ShaderCompiler sc;
	std::vector<ShaderParams> functionParams;
	ShaderFunction func;
	std::unique_ptr<VerticesShape> verts;
};

