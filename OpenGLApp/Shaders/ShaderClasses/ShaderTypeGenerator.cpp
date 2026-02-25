#include "ShaderTypeGenerator.h"
#include "..\..\Camera\Camera.h"

ShaderTypeGenerator::ShaderTypeGenerator()
{
}

void ShaderTypeGenerator::ShaderDiffuseGenerator(std::vector<Shader*>& shaders, unsigned int program, std::vector<ShaderParams>& params)
{
	glm::mat4 model = std::get<glm::mat4>(params[0]);
	glm::vec3 outsideLight = std::get<glm::vec3>(params[1]);
	bool isShadow = std::get<bool>(params[2]);
	if (isShadow)
	{
		glm::mat4 lightSpaceMatrix = std::get<glm::mat4>(params[3]);;
		shaders[0]->SetUniformMat4f("lightSpaceMatrix", lightSpaceMatrix, program);
	}
	else
	{
		shaders[0]->SetUniformMat4f("lightSpaceMatrix", glm::mat4(1.0f), program);
	}
	shaders[0]->SetUniformMat4f("model", model, program);

	shaders[1]->SetUniform1i("material.diffuse", 0, program);
	shaders[1]->SetUniform1i("material.specular", 1, program);
	shaders[1]->SetUniform1i("shadowMap", 7, program);

	shaders[1]->SetUniform3f("light.lightPos", outsideLight, program);
	shaders[1]->SetUniform3f("light.ambient", glm::vec3(0.2f, 0.2f, 0.2f), program);
	shaders[1]->SetUniform3f("light.diffuse", glm::vec3(1.0f, 1.0f, 1.0f), program);
	shaders[1]->SetUniform3f("light.specular", glm::vec3(1.0f, 1.0f, 1.0f), program);

	shaders[1]->SetUniform1f("light.constant", 1.0f, program);
	shaders[1]->SetUniform1f("light.linear", 0.2f, program);
	shaders[1]->SetUniform1f("light.quadratic", 0.2f, program);

	shaders[1]->SetUniform3f("material.ambient", glm::vec3(1.0f, 1.0f, 1.0f), program);
	shaders[1]->SetUniform1f("material.shininess", 32.0f, program);

	shaders[1]->SetUniform3f("camPos", CameraManager::camManager->GetActiveCamera()->GetCamPos(), program);
	shaders[1]->SetUniform3f("sunLight", 0.99f, 0.71f, 0.32f, program);
	shaders[1]->SetUniform3f("skyLight", 0.51f, 0.80f, 0.92f, program);

}

void ShaderTypeGenerator::PassLightMatrixData(std::vector<Shader*>& shaders, unsigned int program, std::vector<ShaderParams>& params)
{
	shaders[1]->SetUniform1i("shadowMap", 7, program);
}

void ShaderTypeGenerator::GBuffer(std::vector<Shader*>& shaders, unsigned int program, std::vector<ShaderParams>& params)
{
	glm::mat4 model = std::get<glm::mat4>(params[0]);
	shaders[0]->SetUniformMat4f("model", model, program);
	shaders[1]->SetUniform1i("diffuse", 0, program);
	shaders[1]->SetUniform1i("specular", 1, program);
}

void ShaderTypeGenerator::ShaderLightGenerator()
{
}

void ShaderTypeGenerator::ShaderAlphaDiffuseGenerator()
{
}


void ShaderTypeGenerator::ShaderLightDiffuseGenerator(std::vector<Shader*>& shaders, unsigned int program, std::vector<ShaderParams>& params)
{
	glm::mat4 model = std::get<glm::mat4>(params[0]);
	glm::vec4 color = std::get<glm::vec4>(params[1]);
	UpdateModel(shaders, program, model);
	UpdateColor(shaders, program, color);
}

void ShaderTypeGenerator::ShaderSkyBoxGenerator(std::vector<Shader*>& shaders, unsigned int program)
{
	shaders[1]->SetUniform1i("cubemap", 0, program);
}

void ShaderTypeGenerator::PostProcesingShaderGenerator(std::vector<Shader*>& shaders, unsigned int program, std::vector<ShaderParams>& params)
{
	shaders[1]->SetUniform1i("screenTexture", 0, program);
}

void ShaderTypeGenerator::HDRShaderGenerator(std::vector<Shader*>& shaders, unsigned int program, std::vector<ShaderParams>& params)
{
	shaders[1]->SetUniform1i("hdrTexture", 0, program);
}

void ShaderTypeGenerator::HDRGaussianBlurShaderGenerator(std::vector<Shader*>& shaders, unsigned int program, std::vector<ShaderParams>& params)
{
	shaders[1]->SetUniform1i("scene", 0, program);
	//shaders[1]->SetUniform1i("bloom", 1, program);
	shaders[1]->SetUniform1f("exposure", 1.0f, program);
}

void ShaderTypeGenerator::PickedShaderGenerator(std::vector<Shader*>& shaders, unsigned int program, std::vector<ShaderParams>& params)
{
	//BaseMVPVertexShaderGenerator(shaders[0], mvp, program);
	glm::mat4 model = std::get<glm::mat4>(params[0]);
	glm::vec3 color = std::get<glm::vec3>(params[1]);
	shaders[0]->SetUniformMat4f("model", model, program);
	shaders[1]->SetUniform3f("PickingColor", color, program);
}

void ShaderTypeGenerator::ShaderDisplacementGenerator(std::vector<Shader*>& shaders, unsigned int program, std::vector<ShaderParams>& params)
{
	glm::mat4 model = std::get<glm::mat4>(params[0]);
	glm::vec3 outsideLight = std::get<glm::vec3>(params[1]);

	outsideLight = glm::vec3(0.0f);

	shaders[0]->SetUniformMat4f("model", model, program);
	shaders[0]->SetUniform3f("camPos", CameraManager::camManager->GetActiveCamera()->GetCamPos(), program);
	shaders[0]->SetUniform3f("lightPos", outsideLight, program);

	shaders[1]->SetUniform1i("diffuse", 0, program);
	shaders[1]->SetUniform1i("normalMap", 1, program);
	shaders[1]->SetUniform1i("depthMap", 2, program);
}

void ShaderTypeGenerator::BaseMVPVertexShaderGenerator(Shader* vertexShader, unsigned int program, MVP& mvp)
{
	vertexShader->SetUniformMat4f("model", mvp.model, program);
	vertexShader->SetUniformMat4f("projection", mvp.proj, program);
	vertexShader->SetUniformMat4f("view", mvp.view, program);
}

void ShaderTypeGenerator::InstancedTerrainShaderGenerator(std::vector<Shader*>& shaders, unsigned int program, std::vector<ShaderParams>& params)
{
	glm::mat4 model = std::get<glm::mat4>(params[0]);
	glm::vec3 outsideLight = std::get<glm::vec3>(params[1]);
	glm::vec3 offset = std::get<glm::vec3>(params[2]);
	unsigned int instanceNumber = std::get<unsigned int>(params[3]);
	bool isShadow = std::get<bool>(params[4]);
	glm::mat4 lightSpaceMatrix = std::get<glm::mat4>(params[5]);
	shaders[0]->SetUniformMat4f("model", model, program);
	shaders[0]->SetUniform3f("offset[" + std::to_string(instanceNumber) + "]", offset, program);
	shaders[0]->SetUniformMat4f("lightSpaceMatrix", lightSpaceMatrix, program);
	shaders[1]->SetUniform1i("terrainTexture", 0, program);
	shaders[1]->SetUniform1i("shadowMap", 7, program);

	shaders[1]->SetUniform1i("material.diffuse", 1, program);
	shaders[1]->SetUniform1i("material.specular", 2, program);
	shaders[1]->SetUniform3f("light.lightPos", outsideLight, program);
	shaders[1]->SetUniform3f("light.ambient", glm::vec3(0.2f, 0.2f, 0.2f), program);
	shaders[1]->SetUniform3f("light.diffuse", glm::vec3(1.0f, 1.0f, 1.0f), program);
	shaders[1]->SetUniform3f("light.specular", glm::vec3(1.0f, 1.0f, 1.0f), program);

	shaders[1]->SetUniform1f("light.constant", 1.0f, program);
	shaders[1]->SetUniform1f("light.linear", 0.2f, program);
	shaders[1]->SetUniform1f("light.quadratic", 0.2f, program);

	shaders[1]->SetUniform3f("material.ambient", glm::vec3(1.0f, 1.0f, 1.0f), program);
	shaders[1]->SetUniform1f("material.shininess", 32.0f, program);

	shaders[1]->SetUniform3f("camPos", CameraManager::camManager->GetActiveCamera()->GetCamPos(), program);
	shaders[1]->SetUniform3f("sunLight", 0.99f, 0.71f, 0.32f, program);
	shaders[1]->SetUniform3f("skyLight", 0.51f, 0.80f, 0.92f, program);
}

void ShaderTypeGenerator::LightShadowShaderGenerator(std::vector<Shader*>& shaders, unsigned int program, std::vector<ShaderParams>& params)
{
	glm::mat4 lightSpaceMatrix = std::get<glm::mat4>(params[0]);
	glm::mat4 model = std::get<glm::mat4>(params[1]);
	glm::vec3 offset = std::get<glm::vec3>(params[2]);
	unsigned int instanceNumber = std::get<unsigned int>(params[3]);
	shaders[0]->SetUniformMat4f("model", model, program);
	shaders[0]->SetUniformMat4f("lightSpaceMatrix", lightSpaceMatrix, program);
	shaders[0]->SetUniform3f("offset[" + std::to_string(instanceNumber) + "]", offset, program);
}

void ShaderTypeGenerator::UpdateBloomShader(std::vector<Shader*>& shaders, unsigned int program, std::vector<ShaderParams>& params)
{
	bool horizontal = std::get<bool>(params[0]);
	shaders[1]->SetUniform1i("bloomTexture", 0, program);
	shaders[1]->SetUniform1i("horizontal", horizontal, program);
}

void ShaderTypeGenerator::UpdateModel(std::vector<Shader*>& shaders, unsigned int program, glm::mat4& model)
{
	shaders[0]->SetUniformMat4f("model", model, program);
}
void ShaderTypeGenerator::UpdateColor(std::vector<Shader*>& shaders, unsigned int program, glm::vec4& color)
{
	shaders[1]->SetUniform4f("color", color, program);
}

void ShaderTypeGenerator::UpdateColorParam(std::vector<Shader*>& shaders, unsigned int program, std::vector<ShaderParams>& params)
{
	glm::vec4 color = std::get<glm::vec4>(params[0]);
	shaders[1]->SetUniform4f("color", color, program);
}

void ShaderTypeGenerator::UpdateColorWithoutAlphaParam(std::vector<Shader*>& shaders, unsigned int program, glm::vec3& color)
{
	shaders[1]->SetUniform3f("color", color, program);
}


void ShaderTypeGenerator::UpdateTexture(std::vector<Shader*>& shaders, unsigned int program, unsigned short slot)
{
	shaders[1]->SetUniform1i("diffuse", slot, program);
}

void ShaderTypeGenerator::UpdateModelWithColor(std::vector<Shader*>& shaders, unsigned int program, std::vector<ShaderParams>& params)
{
	glm::mat4 model = std::get<glm::mat4>(params[0]);
	glm::vec4 color = std::get<glm::vec4>(params[1]);
	UpdateModel(shaders, program, model);
	UpdateColor(shaders, program, color);
}

void ShaderTypeGenerator::UpdateModelColorandTexture(std::vector<Shader*>& shaders, unsigned int program, std::vector<ShaderParams>& params)
{
	glm::mat4 model = std::get<glm::mat4>(params[0]);
	glm::vec4 color = std::get<glm::vec4>(params[1]);
	unsigned short slot = std::get<unsigned short>(params[2]);
	UpdateModel(shaders, program, model);
	UpdateColor(shaders, program, color);
	UpdateTexture(shaders, program, slot);
}

void ShaderTypeGenerator::UpdateLightiningHDR(std::vector<Shader*>& shaders, unsigned int program, std::vector<ShaderParams>& params)
{
	glm::mat4 model = std::get<glm::mat4>(params[0]);
	UpdateModel(shaders, program, model);
	shaders[0]->SetUniform3f("camPos", CameraManager::camManager->GetActiveCamera()->GetCamPos(), program);
	std::vector<SimpleLight> lights = std::get <std::vector<SimpleLight>>(params[2]);

	for (auto& light : lights)
	{
		//UpdateColorWithoutAlphaParam(shaders, program, light.color);
		UpdateTexture(shaders, program, light.slot);
		shaders[1]->SetUniform3f("simpleLights[" + std::to_string(light.lightNumber) + "].position", light.position, program);
		shaders[1]->SetUniform3f("simpleLights[" + std::to_string(light.lightNumber) + "].color", light.color, program);
		shaders[1]->SetUniform3f("simpleLights.ambient", glm::vec3(0.2f, 0.2f, 0.2f), program);
	}
}

void ShaderTypeGenerator::UpdateFinalBloomShader(std::vector<Shader*>& shaders, unsigned int program, std::vector<ShaderParams>& params)
{
	float exposure = std::get<float>(params[0]);
	shaders[1]->SetUniform1i("scene", 0, program);
	shaders[1]->SetUniform1i("bloom", 1, program);
	shaders[1]->SetUniform1f("exposure", exposure, program);
}


void ShaderTypeGenerator::BloomShaderGenerator(std::vector<Shader*>& shaders, unsigned int program, std::vector<ShaderParams>& params)
{
	glm::mat4 model = std::get<glm::mat4>(params[0]);
	glm::vec3 lightPos = std::get<glm::vec3>(params[1]);
	glm::vec3 lightColor = std::get<glm::vec3>(params[2]);

	UpdateModel(shaders, program, model);
	shaders[1]->SetUniform1i("diffuseTexture", 0, program);
	shaders[1]->SetUniform3f("lightPosition", lightPos, program);
	shaders[1]->SetUniform3f("lightColor", lightColor, program);

}

void ShaderTypeGenerator::DefferedShading(std::vector<Shader*>& shaders, unsigned int program, std::vector<ShaderParams>& params)
{
	std::vector<SimpleLight> lights = std::get <std::vector<SimpleLight>>(params[0]);
	shaders[1]->SetUniform1i("pos", 0, program);
	shaders[1]->SetUniform1i("normal", 1, program);
	shaders[1]->SetUniform1i("albedoSpec", 2, program);
	shaders[1]->SetUniform3f("viewPos", CameraManager::camManager->GetActiveCamera()->GetCamPos(), program);
	for (auto& light : lights)
	{
		for (auto& light : lights)
		{
			shaders[1]->SetUniform3f("lights[" + std::to_string(light.lightNumber) + "].position", light.position, program);
			shaders[1]->SetUniform3f("lights[" + std::to_string(light.lightNumber) + "].color", light.color, program);
			shaders[1]->SetUniform1f("lights[" + std::to_string(light.lightNumber) + "].linear", 0.09f, program);    // typical small linear
			shaders[1]->SetUniform1f("lights[" + std::to_string(light.lightNumber) + "].quadratic", 0.032f, program); // typical quadratic
			shaders[1]->SetUniform1f("lights[" + std::to_string(light.lightNumber) + "].radius", 10.0f, program);
		}
	}
}

void ShaderTypeGenerator::SSAOShaderGenerator(std::vector<Shader*>& shaders, unsigned int program, std::vector<ShaderParams>& params)
{
	shaders[1]->SetUniform1i("gPosition", 0, program);
	shaders[1]->SetUniform1i("gNormal", 1, program);
	shaders[1]->SetUniform1i("texNoise", 2, program);
	std::vector<glm::vec3> ssaoKernel = std::get<std::vector<glm::vec3>>(params[0]);
	shaders[1]->SetUniformMat4f("projection", std::get<glm::mat4>(params[1]), program);
	for (unsigned int i = 0; i < ssaoKernel.size(); ++i)
	{
		shaders[1]->SetUniform3f("samples[" + std::to_string(i) + "]", ssaoKernel[i], program);
	}
}

ShaderTypeGenerator::~ShaderTypeGenerator()
{
}
