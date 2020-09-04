#include "SkyBoxCube.h"



SkyBoxCube::SkyBoxCube(const ShapesBuilder builder)
{
	GLfloat g_vertex_buffer_data[] = {
		-10.0f, -10.0f, 10.0f,//0
		 10.0f, 10.0f, 10.0f,//1
		-10.0f,  10.0f, 10.0f,//2
		10.0f, -10.0f, 10.0f,//3
		-10.0f, -10.0f, -10.0f,// 4
		10.0f, 10.0f, -10.0f,// 5
		-10.0f,  10.0f, -10.0f,// 6
		10.0f, -10.0f, -10.0f};// 7
	unsigned int indexes[] = { 4, 7, 5, 
		5, 6, 4,
		0, 4, 6,
		6, 2, 0,
		3, 7, 5,
		5, 1, 3,
		0, 3, 1,
		1, 2, 0,
		2, 6, 5,
		5, 1, 2,
		0, 4, 7,
		7, 3, 0 };

	CreateType();
	CreateShape(g_vertex_buffer_data, indexes, 12, 36);
}

void SkyBoxCube::CreateShape(const GLfloat * points, unsigned int * orderIndex, unsigned int countVertices, unsigned int countIndexes)
{
	GLCall(glEnable(GL_BLEND));
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

	va = new VertexArray();
	vb = new VertexBuffer(points, sizeof(float) * countVertices * (3));
	layout = new VertexBufferLayout();
	layout->Push<float>(3); // vertexes
	va->AddBuffer(*vb, *layout);
	ib = new IndexBuffer(orderIndex, countIndexes); //indexes count
}

void SkyBoxCube::GenerateShaders()
{
	//to-do pls karol wake up
	shaders.push_back(new Shader("Shaders\\SimpleShaderCubeBox.vert"));
	shaders.push_back(new Shader("Shaders\\SimpleShaderCubeBox.frag"));
	sm.AddShadersToProgram(shaders);
	sm.Bind();
	CreateMVPMatrix();
	paths.push_back("Images\\SkyBox\\ss_rt.tga");
	paths.push_back("Images\\SkyBox\\ss_lf.tga");
	paths.push_back("Images\\SkyBox\\ss_up.tga");
	paths.push_back("Images\\SkyBox\\ss_dn.tga");
	paths.push_back("Images\\SkyBox\\ss_ft.tga");
	paths.push_back("Images\\SkyBox\\ss_bk.tga");
	glDepthFunc(GL_LEQUAL);
	cubeMapTexture = new CubeMapTexture(paths);
	cubeMapTexture->Bind();

	ShaderTypeGenerator::ShaderSkyBoxGenerator(shaders, mvp, sm.GetProgram());

	cubeMapTexture->UnBind();
	glDepthFunc(GL_LESS);
	shapeState = ShapeState::EXISTING;
}

void SkyBoxCube::CreateMVPMatrix()
{
	//mvp.model = glm::mat4(0.0f);
	//mvp.model = glm::scale(mvp.model, glm::vec3(1.0f, 1.0f, 1.0f));
}

void SkyBoxCube::Update()
{
	glDepthFunc(GL_LEQUAL);
	sm.Bind();
	cubeMapTexture->Bind();
	//shaders[0]->SetUniformMat4f("model", mvp.model, sm.GetProgram());
	shaders[0]->SetUniformMat4f("projection", mvp.proj, sm.GetProgram());
	shaders[0]->SetUniformMat4f("view", mvp.view, sm.GetProgram());
	sm.UnBind();
	sm.Bind();
	ib->Bind();
	va->Bind();
	glDepthFunc(GL_LESS);
}
void SkyBoxCube::InitializeShapeView(glm::mat4 & view)
{
	if (shapeState == ShapeState::EXISTING)
	{
		glm::vec4 cubeMapView = glm::vec4(this->mvp.view[3][0], this->mvp.view[3][1],
			this->mvp.view[3][2], this->mvp.view[3][3]);
		this->mvp.view = view;
		this->mvp.view[3] = cubeMapView;
	}
	else

	{
		this->mvp.view = view;
	}
}
glm::vec3 SkyBoxCube::GetNormal()
{
	return glm::vec3();
}
SkyBoxCube::~SkyBoxCube()
{
}

