#include "StencilOutline.h"

StencilOutline::StencilOutline()
{
	mvpOutline.model = glm::mat4(1.0f);
	shaders.push_back(new Shader("Shaders\\PickingVertexShader.vert"));
	shaders.push_back(new Shader("Shaders\\PickingFragmentShader.frag"));
	sm.AddShadersToProgram(shaders);
	sm.Bind();
}

void StencilOutline::InitializeView(glm::mat4& camView)
{
	mvpOutline.view = camView;
}

void StencilOutline::InitializePerspective(glm::mat4& perspective)
{
	mvpOutline.proj = perspective;
}
void StencilOutline::InitializeModel(glm::mat4& model)
{
	mvpOutline.model = model;
	float scale = 1.01f;
	mvpOutline.model = glm::scale(mvpOutline.model, glm::vec3(scale));
}

void StencilOutline::CalculateMvpResult()
{
	mvpResult = mvpOutline.proj * mvpOutline.view * mvpOutline.model;
}

void StencilOutline::UseShader()
{
	ShaderTypeGenerator::PickedShaderGenerator(shaders, glm::vec3(0.0f, 1.0f, 0.0f), mvpResult, sm.GetProgram());
}

void StencilOutline::Update()
{
	CalculateMvpResult();
	sm.Bind();
	UseShader();

}
