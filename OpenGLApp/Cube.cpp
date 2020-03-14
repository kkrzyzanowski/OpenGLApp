#include "Cube.h"



Cube::Cube(const ShapesBuilder builder): Shape()
{
	GLfloat g_vertex_buffer_data[] = {
		-.5f, -.5f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,//0
		.5f, .5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,//1
		-.5f,  0.5f, 0.5f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,//2
		.5f, -.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,//3
		-.5f, -.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f,// 4
		0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f,// 5
		-.5f,  0.5f, -0.5f, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f,// 6
		0.5f, -.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, -1.0f, };// 7
	unsigned int indexes[] = { 0, 3, 1,
		1, 2, 0,
		0, 4, 2,
		2, 4, 6,
		6, 4, 5,
		5, 4, 7,
		7, 5, 1,
		1, 3, 7,
		7, 4, 3,
		3, 0, 4,
		5, 6, 1,
		1, 2, 6 };
	CreateShape(g_vertex_buffer_data, indexes, 12, 36);
}




Cube::~Cube()
{
}

void Cube::GenerateShaders()
{
	textures.push_back(new Texture("Images\\BrickMedievalBlocks0129_2_M.jpg", 0));
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
void Cube::CreateMVPMatrix()
{
	mvp.model = glm::mat4(1.0f);
	mvp.model = glm::translate(mvp.model, glm::vec3(0.6f, -0.8f, .7f));
	mvp.view = glm::mat4(1.0f);
	mvp.view = glm::translate(mvp.view, glm::vec3(0.0f, 0.0f, 0.5f));
	mvpResult = mvp.proj * mvp.view * mvp.model;
}


void Cube::Update()
{
	sm.Bind();
	for each(Texture* texture in textures)
		texture->Bind();
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
glm::vec3 Cube::GetNormal()
{
	return glm::vec3();
}
//template <typename Matrix, typename ... glm::mat4>
//void Cube::TransformateShape(Matrix arg, glm::mat4&... rest)
//{
//	result *= arg;
//	TransformateShape(rest...);
//}
