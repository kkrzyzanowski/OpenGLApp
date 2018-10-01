#include "Plane.h"



Plane::Plane(): Shape(Shapes::RECTANGLE)
{
	GLfloat g_vertex_buffer_data[20] = {
		-.5f, -.5f, -1.0f, 0.0f, 0.0f,//0
		.5f, -.5f, -1.0f, 1.0f, 0.0f, //1
		-.5f,  -.5f, 1.0f, 0.0f, 1.0f, //2
		.5f, -.5f, 1.0f, 1.0f, 1.0f, //3
	};
	unsigned int indexes[] = {
		0, 2, 3,
		0, 1, 3,
	};
	CreateShape(g_vertex_buffer_data, indexes);
}

void Plane::CreateShape(const GLfloat * points, unsigned int * orderIndex)
{
	GLCall(glEnable(GL_BLEND));
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));


	texture = new Texture("Images\\BrickMedievalBlocks0129_2_M.jpg");
	va = new VertexArray();
	vb = new VertexBuffer(points, sizeof(float) * 4 * 3 * 2);

	layout = new VertexBufferLayout();
	layout->Push<float>(3); // vertexes
	layout->Push<float>(2); //textcoorssd
	va->AddBuffer(*vb, *layout);
	ib = new IndexBuffer(orderIndex, 6); //indexes count
	GenerateShaders();
}

void Plane::GenerateShaders()
{
	shaders.push_back(new Shader("Shaders\\VertexShaderPlane.vert"));
	shaders.push_back(new Shader("Shaders\\FragmentShaderPlane.frag"));
	sm.AddShadersToProgram(shaders);
	sm.Bind();
	CreateMVPMatrix();
	shaders[0]->SetUniformMat4f("u_MVP", mvp, sm.GetProgram());
	texture->Bind();
	shaders[1]->SetUniform4f("u_color", 1.0f, 1.0f, 1.0f, 1.0f, sm.GetProgram());
	shaders[1]->SetUniform1i("u_texture", 0, sm.GetProgram());
	shaders[1]->SetUniform3f("sunLight", 0.99f, 0.71f, 0.32f, sm.GetProgram());
	shaders[1]->SetUniform3f("skyLight", 0.51f, 0.80f, 0.92f, sm.GetProgram());
}
void Plane::CreateMVPMatrix()
{
	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0.0f, -3.0f, 10.0f));
	model = glm::scale(model, glm::vec3(50.0f, 1.0f, 5.0f));
	view = glm::mat4(1.0f);
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -.5f));
	proj = glm::perspective(glm::radians(90.0f), 16.0f / 9.0f, 0.01f, 100.0f);
	mvp = proj * view * model;
}
void Plane::TurnOffShapeElements()
{
	va->UnBind();
	vb->UnBind();
	ib->UnBind();
	sm.UnBind();
}

void Plane::Update(glm::mat4 camView)
{
	sm.Bind();
	shaders[0]->SetUniformMat4f("u_camView", camView, sm.GetProgram());
	sm.UnBind();
	sm.Bind();
	ib->Bind();
	va->Bind();
}


Plane::~Plane()
{
}
