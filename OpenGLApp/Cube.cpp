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
		1, 3, 7 };
	CreateShape(g_vertex_buffer_data, indexes);
}

void Cube::CreateShape(const GLfloat * points, unsigned int * orderIndex)
{
	GLCall(glEnable(GL_BLEND));
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));


	texture = new Texture("Images\\BrickMedievalBlocks0129_2_M.jpg");
	va = new VertexArray();
	vb = new VertexBuffer(points, sizeof(float) * 8 * (3 + 2 + 3));

	layout = new VertexBufferLayout();
	layout->Push<float>(3); // vertexes
	layout->Push<float>(2); //textcoorssd
	layout->Push<float>(3); // normals
	va->AddBuffer(*vb, *layout);
	ib = new IndexBuffer(orderIndex, 24); //indexes count
	GenerateShaders();
	
}


Cube::~Cube()
{
}

void Cube::GenerateShaders()
{
	shaders.push_back(new Shader("Shaders\\VertexShaderCube.vert"));
	shaders.push_back(new Shader("Shaders\\FragmentShaderCube.frag"));
	sm.AddShadersToProgram(shaders);
	sm.Bind();
	CreateMVPMatrix();
	shaders[0]->SetUniformMat4f("u_MVP", mvp, sm.GetProgram());
	texture->Bind();
	shaders[1]->SetUniform4f("u_color", 0.9f, 0.4f, 0.6f, 0.8f, sm.GetProgram());
	shaders[1]->SetUniform1i("u_texture", 0, sm.GetProgram());
}
void Cube::CreateMVPMatrix()
{
	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0.6f, -0.8f, -.7f));
	view = glm::mat4(1.0f);
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, 0.5f));
	proj = glm::perspective(glm::radians(90.0f), 16.0f / 9.0f, 0.01f, 100.0f);
	mvp = proj * view * model;
}
void Cube::TurnOffShapeElements()
{
	va->UnBind();
	vb->UnBind();
	ib->UnBind();
	sm.UnBind();
}

void Cube::Update()
{
	sm.Bind();
	//shaders[0]->SetUniformMat4f("u_camView", camView, sm.GetProgram());
	sm.UnBind();
	sm.Bind();
	ib->Bind();
	va->Bind();
}
//template <typename Matrix, typename ... glm::mat4>
//void Cube::TransformateShape(Matrix arg, glm::mat4&... rest)
//{
//	result *= arg;
//	TransformateShape(rest...);
//}
