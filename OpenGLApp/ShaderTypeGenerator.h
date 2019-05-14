#pragma once
#include <vector>
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
	~ShaderTypeGenerator();
};

