#include "LightManager.h"
#include "../Shaders/ShaderClasses/ShaderTypeGenerator.h"
#include "../Lights/Light.h";
#include "../Shapes/Shape.h";
#include "../Shapes/Terrain.h"

std::vector<std::shared_ptr<Light>> LightManager::lights;
std::vector<Shader*> shadowShaders;
LightManager::LightManager()
{
	InitializeShadowShaders();
}

LightManager::~LightManager()
{
}

void LightManager::InitializeShadowProgram(std::shared_ptr<Shape> shape)
{
	if (shape->IsShadowTurnOn())
	{
		shape->sc.CreateProgram("shadows");
		shape->sc.ActivateProgram("shadows");
		shape->sc.AddShadersToProgram(shadowShaders);
	}
}

void LightManager::CreateShadowForLights(std::shared_ptr<Shape> shape)
{
	for (auto& light : lights)
	{
		shape->sc.ActivateProgram("shadows");
		if (glGetError() != GL_NO_ERROR) {
			std::cerr << "Error activating shadow shader program!" << std::endl;
			assert(false);
		}
		shape->sc.EnableUse();
		auto params = light->GetParams();
		params.push_back(shape->GetModel());
		params.push_back(glm::vec3(0.0f));
		params.push_back(unsigned int(0));
		ShaderTypeGenerator::LightShadowShaderGenerator(shadowShaders, shape->sc.GetCurrentProgram(), params);
		shape->bm->BindBuffers();
		break;
	}
}

void LightManager::CreateShadowForLightsTerrain(std::shared_ptr<Terrain> shape)
{
	for (auto& light : lights)
	{
		shape->sc.ActivateProgram("shadows");
		if (glGetError() != GL_NO_ERROR) {
			std::cerr << "Error activating shadow shader program!" << std::endl;
			assert(false);
		}
		shape->sc.EnableUse();
		auto params = light->GetParams();
		glm::vec3* squareOffsets = shape->GetSqareOffsets();
		TerrainProperties tp = shape->GetTerrainProperties();
		params.push_back(shape->GetModel());
		params.push_back(squareOffsets[0]);
		params.push_back(unsigned int(0));
		for (unsigned int i = 0; i < tp.width * tp.height; i++)
		{
			params[2] = squareOffsets[i];
			params[3] = i;
			ShaderTypeGenerator::LightShadowShaderGenerator(shadowShaders, shape->sc.GetCurrentProgram(), params);
		}
		shape->bm->BindBuffers();
		break;
	}
}

void LightManager::ApplyHDRLightParams(std::shared_ptr<Shape> shape, std::vector<ShaderParams>& params)
{
	if (shape->IsHDROn())
	{
		std::vector<SimpleLight> simpleLights;
		shape->sc.EnableUse();
		for (size_t i = 0; i < lights.size(); ++i)
		{
			SimpleLight light;
			light.color = lights[i]->GetColor();
			light.position = lights[i]->Position;
			light.slot = unsigned short(0);
			light.lightNumber = i;
			simpleLights.push_back(light);
		}
		params.push_back(simpleLights);
	}
}

void LightManager::PassLightDataToShape(std::shared_ptr<Shape> shape)
{
	for (auto& light : lights)
	{
		if (shape->IsShadowTurnOn())
			shape->functionParams.push_back(light->LightSpaceMatrix);
		break;
	}
}

void LightManager::InitializeShadowShaders()
{
	shadowShaders.push_back(new Shader(SHADOW_VERT_PATH));
	shadowShaders.push_back(new Shader(SHADOW_FRAG_PATH));
}
