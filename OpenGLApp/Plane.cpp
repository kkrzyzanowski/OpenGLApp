#include "Plane.h"



Plane::Plane()
{
}

Plane::Plane(const ShapesBuilder builder): Shape()
{
	sourceShapeType = builder.m_shapeType;
	camState = builder.m_view;
	light = builder.m_light;
	outsideLight = builder.m_pos;
	GLfloat g_vertex_buffer_data[] = {
		-.5f, -.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,//0
		.5f, -.5f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, //1
		-.5f,  -.5f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,//2
		.5f, -.5f, 1.0f, 1.0f, 1.0f,  0.0f, 1.0f, 0.0f//3
	};
	unsigned int indexes[] = {
		0, 2, 3,
		0, 1, 3,
	};
	CreateShape(g_vertex_buffer_data, indexes, 4, 6);
	CreateType();
}



void Plane::GenerateShaders()
{
	textures.push_back(new Texture("Images\\TexturesCom_Moss0265_8_masked_S.png", 0));
	textures.push_back(new Texture("Images\\BrickMedievalBlocks0129_2_M_specular_map.jpg", 1));
	shaders.push_back(new Shader("Shaders\\DiffuseVertexShader.vert"));
	shaders.push_back(new Shader("Shaders\\DiffuseFragmentShader.frag"));
	sm.AddShadersToProgram(shaders);
	sm.Bind();
	CreateMVPMatrix();
	for each(Texture* texture in textures)
		texture->Bind();
	ShaderTypeGenerator::ShaderDiffuseGenerator(shaders, mvp, outsideLight, sm.GetProgram());
	for each(Texture* texture in textures)
		texture->UnBind();
	shapeState = ShapeState::EXISTING;
}
void Plane::GetSourceLight(glm::vec3 lightSource)
{
	m_sourceLight = lightSource;
}
void Plane::CreateMVPMatrix()
{
	mvp.model = glm::mat4(1.0f);
	mvp.model = glm::translate(mvp.model, glm::vec3(0.0f, 0.0f, 0.0f));
	mvp.model = glm::scale(mvp.model, glm::vec3(50.0f, 1.0f, 5.0f));
	mvp.proj = glm::perspective(glm::radians(90.0f), 16.0f / 9.0f, 0.01f, 100.0f);
	//mvp = proj * view * model;
}

void Plane::Update()
{
	sm.Bind();
	for each(Texture* texture in textures)
		texture->Bind();
	//specularTexture->Bind(1); // slotss
	shaders[0]->SetUniformMat4f("model", mvp.model, sm.GetProgram());
	shaders[0]->SetUniformMat4f("projection", mvp.proj, sm.GetProgram());
	shaders[0]->SetUniformMat4f("view", mvp.view, sm.GetProgram());
	shaders[1]->SetUniform3f("camPos", camEyePos, sm.GetProgram());
	shaders[1]->SetUniform3f("light.lightPos", outsideLight.x, outsideLight.y, outsideLight.y, sm.GetProgram());
	sm.UnBind();
	sm.Bind();
	ib->Bind();
	va->Bind();
}


Plane::~Plane()
{
}
