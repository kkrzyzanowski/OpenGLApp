#include "StencilOutline.h"
#include "../Config.h"

StencilOutline::StencilOutline()
{
	mvpOutline.model = glm::mat4(1.0f);
	shaders.push_back(new Shader(PICKING_VERT_PATH));
	shaders.push_back(new Shader(PICKING_FRAG_PATH));
	sc.AddShadersToProgram(shaders);
	sc.EnableUse();
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
	params.push_back(mvpOutline.model);
}

void StencilOutline::UpdateModel(glm::mat4& model)
{
	mvpOutline.model = model;
	float scale = 1.01f;
	mvpOutline.model = glm::scale(mvpOutline.model, glm::vec3(scale));
	params[0] = mvpOutline.model;
}

void StencilOutline::SetColor(glm::vec3 color)
{
	params.push_back(glm::vec3(0.34f, 0.65f, 0.11f));
}

void StencilOutline::BindMVMatrices()
{
	sc.BindBlockData("Matrices");
}

void StencilOutline::UseShader()
{
	ShaderTypeGenerator::PickedShaderGenerator(shaders, sc.GetDefaultProgram(), params);
}

void StencilOutline::Update()
{
	sc.EnableUse();
	UseShader();

}
