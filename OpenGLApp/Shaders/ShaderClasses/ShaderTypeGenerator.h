#pragma once
#include <vector>
#include <array>
#include "Shader.h"
#include "..\..\DataStructures.h"

static class ShaderTypeGenerator
{
public:
	ShaderTypeGenerator();
	static void ShaderDiffuseGenerator(std::vector<Shader*> &shaders, unsigned int program, std::vector<ShaderParams>& params);
	static void ShaderLightGenerator();
	static void ShaderAlphaDiffuseGenerator();
	static void ShaderLightDiffuseGenerator(std::vector<Shader*>& shaders, unsigned int program, std::vector<ShaderParams>& params);
	static void ShaderSkyBoxGenerator(std::vector<Shader*>& shaders, unsigned int program);
	static void PostProcesingShaderGenerator(std::vector<Shader*>& shaders, unsigned int program, std::vector<ShaderParams>& params);
	static void HDRShaderGenerator(std::vector<Shader*>& shaders, unsigned int program, std::vector<ShaderParams>& params);
	static void HDRGaussianBlurShaderGenerator(std::vector<Shader*>& shaders, unsigned int program, std::vector<ShaderParams>& params);
	static void PickedShaderGenerator(std::vector<Shader*>& shaders, unsigned int program, std::vector<ShaderParams>& params);
	static void ShaderDisplacementGenerator(std::vector<Shader*>& shaders, unsigned int program, std::vector<ShaderParams>& params);
	static void BaseMVPVertexShaderGenerator(Shader* vertexShader, unsigned int program, MVP& mvp);
	static void InstancedTerrainShaderGenerator(std::vector<Shader*>& shaders, unsigned int program, std::vector<ShaderParams>& params);
	static void LightShadowShaderGenerator(std::vector<Shader*>& shaders, unsigned int program, std::vector<ShaderParams>& params);
	static void UpdateBloomShader(std::vector<Shader*>& shaders, unsigned int program, std::vector<ShaderParams>& params);
	static void UpdateModel(std::vector<Shader*>& shaders, unsigned int program, glm::mat4& model);
	static void UpdateColorParam(std::vector<Shader*>& shaders, unsigned int program, std::vector<ShaderParams>& params);
	static void UpdateColorWithoutAlphaParam(std::vector<Shader*>& shaders, unsigned int program, glm::vec3& color);
	static void UpdateColor(std::vector<Shader*>& shaders, unsigned int program, glm::vec4& color);
	static void UpdateTexture(std::vector<Shader*>& shaders, unsigned int program, unsigned short slot);
	static void PassLightMatrixData(std::vector<Shader*>& shaders, unsigned int program, std::vector<ShaderParams>& params);
	static void GBuffer(std::vector<Shader*>& shaders, unsigned int program, std::vector<ShaderParams>& params);
	static void UpdateModelWithColor(std::vector<Shader*>& shaders, unsigned int program, std::vector<ShaderParams>& params);
	static void UpdateModelColorandTexture(std::vector<Shader*>& shaders, unsigned int program, std::vector<ShaderParams>& params);
	static void UpdateLightiningHDR(std::vector<Shader*>& shaders, unsigned int program, std::vector<ShaderParams>& params);
	static void UpdateFinalBloomShader(std::vector<Shader*>& shaders, unsigned int program, std::vector<ShaderParams>& params);
	static void PassDataToShader(std::vector<Shader*>& shader, unsigned int program);
	static void BloomShaderGenerator(std::vector<Shader*>& shaders, unsigned int program, std::vector<ShaderParams>& params);
	~ShaderTypeGenerator();
};
