#include "SkyBoxCube.h"
#include "../Config.h"



SkyBoxCube::SkyBoxCube(ShapesBuilder& builder): Shape(builder)
{
	GLfloat g_vertex_buffer_data[] = {
		-10.0f, -10.0f, 10.0f,//0
		 10.0f, -10.0f, 10.0f,//1
		10.0f,  -10.0f, -10.0f,//2
		-10.0f, -10.0f, -10.0f,//3
		-10.0f, 10.0f, 10.0f,// 4
		10.0f, 10.0f, 10.0f,// 5
		10.0f,  10.0f, -10.0f,// 6
		-10.0f, 10.0f, -10.0f};// 7
	unsigned int indexes[] = { 
		// Right
	1, 2, 6,
	6, 5, 1,
	// Left
	0, 4, 7,
	7, 3, 0,
	// Top
	4, 5, 6,
	6, 7, 4,
	// Bottom
	0, 3, 2,
	2, 1, 0,
	// Back
	0, 1, 5,
	5, 4, 0,
	// Front
	3, 7, 6,
	6, 2, 3
	};
	CreateType();
	Create(g_vertex_buffer_data, indexes, 12, 36, nullptr, 8);
}


SkyBoxCube::SkyBoxCube(ShapesBuilder&& builder) : Shape(std::move(builder))
{
	GLfloat g_vertex_buffer_data[] = {
		-10.0f, -10.0f, 10.0f,//0
		 10.0f, -10.0f, 10.0f,//1
		10.0f,  -10.0f, -10.0f,//2
		-10.0f, -10.0f, -10.0f,//3
		-10.0f, 10.0f, 10.0f,// 4
		10.0f, 10.0f, 10.0f,// 5
		10.0f,  10.0f, -10.0f,// 6
		-10.0f, 10.0f, -10.0f };// 7
	unsigned int indexes[] = {
		// Right
	1, 2, 6,
	6, 5, 1,
	// Left
	0, 4, 7,
	7, 3, 0,
	// Top
	4, 5, 6,
	6, 7, 4,
	// Bottom
	0, 3, 2,
	2, 1, 0,
	// Back
	0, 1, 5,
	5, 4, 0,
	// Front
	3, 7, 6,
	6, 2, 3
	};
	CreateType();
	Create(g_vertex_buffer_data, indexes, 12, 36, nullptr, 8);
}

void SkyBoxCube::Create(const GLfloat * points, unsigned int * orderIndex, unsigned int countVertices, unsigned int countIndexes, unsigned int* bufferDataSizes, unsigned int dataSize)
{
	GLCall(glEnable(GL_BLEND));
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
	bm->CreateBuffersOnlyVertex(points, orderIndex, countVertices, countIndexes);
}

void SkyBoxCube::GenerateShaders()
{
	sc.ActivateDefaultProgram();
	sc.AddShadersToProgram(sm->shaders);
	sc.EnableUse();
	PrepareShaderMatricesFieldData();
	CreateMVPMatrix();
	paths.push_back(CUBEBOX_RIGHT_PATH);
	paths.push_back(CUBEBOX_LEFT_PATH);
	paths.push_back(CUBEBOX_TOP_PATH);
	paths.push_back(CUBEBOX_BOTTOM_PATH);
	paths.push_back(CUBEBOX_FRONT_PATH);
	paths.push_back(CUBEBOX_BACK_PATH);
	
	shapeState = ShapeState::EXISTING;
}

void SkyBoxCube::ApplyShaders()
{
	glDepthFunc(GL_LEQUAL);
	cubeMapTexture = new CubeMapTexture(paths);
	cubeMapTexture->Bind();
	ShaderTypeGenerator::ShaderSkyBoxGenerator(sm->shaders, sc.GetDefaultProgram());
	cubeMapTexture->UnBind();
	glDepthFunc(GL_LESS);
}

void SkyBoxCube::CreateMVPMatrix()
{
}

void SkyBoxCube::Update()
{
	glDepthFunc(GL_LEQUAL);
	sc.EnableUse();
	cubeMapTexture->Bind();
	ActivateShapeBufferParts();
	//sc.DisableUse();
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
	delete cubeMapTexture;
}

