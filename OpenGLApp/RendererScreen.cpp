#include "RendererScreen.h"

RendererScreen::RendererScreen() : bufferManager(std::make_unique<BufferManager>()),
shaderManager(std::make_unique<ShaderManager>()),
textureManager(std::make_unique<TextureManager>())
{
	verts = std::unique_ptr<VerticesShape>(CreateQuad());
	InitializeBufferScreenCoords();
}

RendererScreen::RendererScreen(Paths paths, ShaderProperties props) : bufferManager(std::make_unique<BufferManager>()),
shaderManager(std::make_unique<ShaderManager>()),
textureManager(std::make_unique<TextureManager>())
{
	verts = std::unique_ptr<VerticesShape>(CreateQuad());
	InitializeBufferScreenCoords();
	AddTexturesToScreen(paths.texturesPaths);
	sc.ActivateDefaultProgram();
	AddShadersToScreen(paths.shadersPaths);
	sc.AddShadersToProgram(shaderManager->shaders);
	SetFunctionForShaders(props);
}

void RendererScreen::InitializeBufferScreenCoords()
{
	unsigned int bufferDataSizes[2] = { 2, 2 };
	bufferManager->CreateBuffers(verts->Points, verts->Indexes, verts->PointsCount, verts->IndexesCount, bufferDataSizes, 4);
}

void RendererScreen::AddTexturesToScreen(std::vector<const char*> paths)
{
	textureManager->AddTextures(paths);
}

void RendererScreen::AddShadersToScreen(std::vector<const char*> paths)
{
	shaderManager->AddShaders(paths);
}

void RendererScreen::AddParam(ShaderParams& param)
{
	functionParams.push_back(param);
}

void RendererScreen::AddParams(std::vector<ShaderParams>& params)
{
	functionParams.insert(functionParams.end(), params.begin(), params.end());
}

void RendererScreen::UpdateParam(unsigned short index, ShaderParams& value)
{
	functionParams[index] = value;
}


void RendererScreen::SetFunctionForShaders(ShaderProperties props)
{
	switch (props.type)
	{
	case ShaderFunctionType::SHADER_FUNC_BLOOM:
		func = ShaderTypeGenerator::UpdateFinalBloomShader;
		break;
	default:
		break;
	}
	functionParams = props.params;
}

void RendererScreen::Update()
{
	sc.ActivateDefaultProgram();
	sc.EnableUse();
	func(shaderManager->shaders, sc.GetCurrentProgram(), functionParams);
}

void RendererScreen::AfterUpdate() 
{
	sc.DisableUse();
}

RendererScreen::~RendererScreen()
{
}
