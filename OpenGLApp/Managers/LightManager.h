///DO SINGLETON OF THIS
#pragma once
#include <vector>
#include <memory>
#include "ShaderCompiler.h"
#include "..\Shaders\ShaderClasses\ShaderTypeGenerator.h"

class Light;
class Shape;
class Terrain;

static class LightManager
{
public:
	LightManager();
	static std::vector<std::shared_ptr<Light>> lights;
	//static void InsertLight();
	~LightManager();
	static void InitializeShadowProgram(std::shared_ptr<Shape> shape);
	static void CreateShadowForLights(std::shared_ptr<Shape> shape);
	static void CreateShadowForLightsTerrain(std::shared_ptr<Terrain> shape);
	static void ApplyHDRLightParams(std::shared_ptr<Shape> shape, std::vector<ShaderParams>& params);
	static void PassLightDataToShape(std::shared_ptr<Shape> shape);
	static void InitializeShadowShaders();
};

