#include "ShaderTypeGenerator.h"
#include "Camera.h"

ShaderTypeGenerator::ShaderTypeGenerator()
{
}

 void ShaderTypeGenerator::ShaderDiffuseGenerator(std::vector<Shader*> &shaders, MVP &mvp, glm::vec3 &outsideLight, unsigned int program)
{
	shaders[0]->SetUniformMat4f("model", mvp.model, program);
	shaders[0]->SetUniformMat4f("projection", mvp.proj, program);
	shaders[0]->SetUniformMat4f("view", mvp.view, program);

	shaders[1]->SetUniform1i("material.diffuse", 0, program);
	shaders[1]->SetUniform1i("material.specular", 1, program);
	shaders[1]->SetUniform3f("light.lightPos", outsideLight.x, outsideLight.y, outsideLight.y, program);
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

 void ShaderTypeGenerator::ShaderLightGenerator()
 {
 }

 void ShaderTypeGenerator::ShaderAlphaDiffuseGenerator()
 {
 }


 void ShaderTypeGenerator::ShaderLightDiffuseGenerator(std::vector<Shader*> &shaders, glm::mat4& mvp, glm::vec4 &color, unsigned int program)
 {
	 shaders[0]->SetUniformMat4f("u_MVP", mvp, program);
	 shaders[1]->SetUniform4f("u_color", color, program);
	 shaders[1]->SetUniform1i("u_texture", 0, program);
 }

 void ShaderTypeGenerator::ShaderSkyBoxGenerator(std::vector<Shader*>& shaders, MVP & mvp, unsigned int program)
 {
	
	 shaders[0]->SetUniformMat4f("projection", mvp.proj, program);
	 shaders[0]->SetUniformMat4f("view", mvp.view, program);
	 shaders[1]->SetUniform1i("cubemap", 0, program);
 }

 void ShaderTypeGenerator::PostProcesingShaderGenerator(std::vector<Shader*> &shaders, unsigned int program)
 {
	 shaders[1]->SetUniform1i("screenTexture", 0, program);
 }

 void ShaderTypeGenerator::ShaderPrimitiveGenerator(std::vector<Shader*> &shaders, glm::mat4 mvpResult, unsigned int program)
 {
	 shaders[0]->SetUniformMat4f("mvpResult", mvpResult, program);
 }

 void ShaderTypeGenerator::PickedShaderGenerator(std::vector<Shader*>& shaders, glm::vec3& color, glm::mat4& mvpResult, unsigned int program)
 {
	 shaders[0]->SetUniformMat4f("mvpResult", mvpResult, program);
	 shaders[1]->SetUniform3f("PickingColor", color, program);
 }

 void ShaderTypeGenerator::TerrainShaderGenerator(std::vector<Shader*>& shaders, glm::mat4 &mvp, unsigned int program)
 {
	 shaders[0]->SetUniformMat4f("mvpResult", mvp, program);
	 shaders[1]->SetUniform1i("terrainTexture", 0, program);
 }

 ShaderTypeGenerator::~ShaderTypeGenerator()
{
}
