#include "Cube.h"




Cube::Cube(const ShapesBuilder builder) : Shape()
{
	GLfloat g_vertex_buffer_data[] = {
		// front
		-.5f, -.5f, .5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f / sqrt(3.0f),//0
		.5f, -.5f, .5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f / sqrt(3.0f),//3
		.5f, .5f, .5f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f / sqrt(3.0f),//2

		.5f, .5f, .5f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f / sqrt(3.0f),//10
		-.5f, .5f, .5f, 0.0f, 1.0f,  0.0f, 0.0f, 1.0f / sqrt(3.0f),//9
		-.5f, -.5f, .5f, 0.0f, 0.0f,  0.0f, 0.0f, 1.0f / sqrt(3.0f),//8

		// left
		-.5f, -.5f, -.5f, 0.0f, 0.0f, -1.0f / sqrt(3.0f), 0.0f, 0.0f,// 4
		-.5f, -.5f, .5f, 1.0f, 0.0f, -1.0f / sqrt(3.0f), 0.0f, 0.0f,//16
		-.5f,  .5f, .5f, 1.0f, 1.0f, -1.0f / sqrt(3.0f), 0.0f, 0.0f,//1

		-.5f, .5f, .5f, 1.0f, 1.0f, -1.0f / sqrt(3.0f), 0.0f, 0.0f,//17
		-.5f, .5f, -.5f, 0.0f, 1.0f, -1.0f / sqrt(3.0f), 0.0f, 0.0f,// 12
		-.5f, -.5f, -.5f, 0.0f, 0.0f, -1.0f / sqrt(3.0f), 0.0f, 0.0f,// 5

		//top
		-.5f, .5f, .5f, 0.0f, 1.0f, 0.0f, 1.0f / sqrt(3.0f), 0.0f, // 6
		.5f, .5f,  .5f, 1.0f, 1.0f, 0.0f, 1.0f / sqrt(3.0f), 0.0f,// 7
		.5f, .5f, -.5f, 1.0f, 0.0f, 0.0f, 1.0f / sqrt(3.0f), 0.0f,//11

		.5f, .5f, -.5f, 1.0f, 0.0f, 0.0f, 1.0f / sqrt(3.0f), 0.0f,// 13
		-.5f, .5f, -.5f, 0.0f, 0.0f, 0.0f, 1.0f / sqrt(3.0f), 0.0f,// 14
		-.5f, .5f, .5f, 0.0f, 1.0f, 0.0f, 1.0f / sqrt(3.0f), 0.0f,//15

		//right
		.5f, .5f, .5f, 1.0f, 1.0f, 1.0f / sqrt(3.0f), 0.0f, 0.0f,//18
		.5f, -.5f, .5f, 0.0f, 1.0f, 1.0f / sqrt(3.0f), 0.0f, 0.0f,//19
		.5f, -.5f, -.5f, 0.0f, 0.0f, 1.0f / sqrt(3.0f), 0.0f, 0.0f,// 20

		.5f, -.5f, -.5f, 0.0f, 0.0f, 1.0f / sqrt(3.0f), 0.0f, 0.0f,// 21
		.5f, .5f, -.5f, 1.0f, 0.0f, 1.0f / sqrt(3.0f), 0.0f, 0.0f,// 22
		.5f, .5f, .5f, 1.0f, 1.0f, 1.0f / sqrt(3.0f), -0.0f, 0.0f,// 23

		//back
	    .5f, .5f, -.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f / sqrt(3.0f),// 6
		.5f, -.5f, -.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f / sqrt(3.0f),// 7
		-.5f, -.5f, -.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f / sqrt(3.0f),//11

		-.5f, -.5f, -.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f / sqrt(3.0f),// 13
		-.5f, .5f, -0.5f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f / sqrt(3.0f),// 14
		.5f, .5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f / sqrt(3.0f),//15


		//bottom
		.5f, -.5f, .5f, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f / sqrt(3.0f),//18
		-.5f, -.5f, .5f, 0.0f, 1.0f, 0.0f, 0.0f, -1.0f / sqrt(3.0f),//19
		-.5f, -.5f, -.5f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f / sqrt(3.0f),// 20

		-.5f, -.5f, -.5f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f / sqrt(3.0f),// 21
		.5f, -.5f, -.5f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f / sqrt(3.0f),// 22
		.5f, -.5f, .5f, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f / sqrt(3.0f)// 23
	};
	unsigned int indexes[] = { 0, 1, 2,
		3, 4, 5, // front
		6, 7, 8,
		9, 10, 11, // left
		12, 13, 14, 
		15, 16, 17,
		18, 19, 20, 
		21, 22, 23,
		24, 25, 26,
		27, 28, 29, 
		30, 31, 32,
		33, 34, 35, 
	}; // bottom
	
	shapeElements.vertices = GetVertices(g_vertex_buffer_data, 36*8);
	shapeElements.triangles = GetTriangles(shapeElements.vertices, indexes, 36);
	shapeElements.faces = GetFaces(shapeElements.triangles);
	CreateShape(g_vertex_buffer_data, indexes, 36, 36);
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
