#pragma once
#include <vector>
#include <array>
#include "Shader.h"
#include "DataStructures.h"


static class ShaderTypeGenerator
{
public:
	ShaderTypeGenerator();
	static void ShaderDiffuseGenerator(std::vector<Shader*> &shaders, MVP &mvp, glm::vec3 &outsideLight, unsigned int program);
	static void ShaderLightGenerator();
	static void ShaderAlphaDiffuseGenerator();
	static void ShaderNoLightDiffuseGenerator();
	static void ShaderLightDiffuseGenerator(std::vector<Shader*> &shaders, glm::mat4& mvp, glm::vec4 &color, unsigned int program);
	static void ShaderSkyBoxGenerator(std::vector<Shader*> &shaders, MVP &mvp, unsigned int program);
	static void PostProcesingShaderGenerator(std::vector<Shader*> &shaders, unsigned int program);
	static void ShaderPrimitiveGenerator(std::vector<Shader*> &shaders, glm::mat4 mvpResult, unsigned int program);
	static void PickedShaderGenerator(std::vector<Shader*> &shaders,const glm::vec3& color,const glm::mat4& mvpResult, unsigned int program);
	static void TerrainShaderGenerator(std::vector<Shader*>& shaders, glm::mat4 &mvp, unsigned int program);
	~ShaderTypeGenerator();
};

