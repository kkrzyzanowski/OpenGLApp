#include "Plane.h"
#include <iostream>

unsigned int	indexes[] = {
		0, 2, 3,
		0, 1, 3,
};

std::vector<glm::vec3> planeDefaultNormals = { glm::vec3(0.0f, 1.0f, 0.0f),
									glm::vec3(0.0f, 1.0f, 0.0f),
									glm::vec3(0.0f, 1.0f, 0.0f),
									glm::vec3(0.0f, 1.0f, 0.0f) };
Plane::Plane()
{
}

Plane::Plane(const ShapesBuilder builder): Shape()
{
	shapeParams.normals = normals = planeDefaultNormals;
	sourceShapeType = builder.m_shapeType;
	camState = builder.m_view;
	light = builder.m_light;
	outsideLight = builder.m_pos;
	ShapeName = "Plane";
	GLfloat g_vertex_buffer_data[] = {
		-.5f, -.5f, -.5f, 0.0f, 0.0f, normals[0].x, normals[0].y, normals[0].z,//0
		.5f, -.5f, -.5f, 1.0f, 0.0f, normals[1].x, normals[1].y, normals[1].z,//1
		-.5f,  -.5f, .5f, 0.0f, 1.0f, normals[2].x, normals[2].y, normals[2].z,//2
		.5f, -.5f, .5f, 1.0f, 1.0f,  normals[3].x, normals[3].y, normals[3].z,//3
	};

	CreateShape(g_vertex_buffer_data, indexes, 4, 6);

	//verts = GetVertices(g_vertex_buffer_data, 4 * 8);
	shapeElements.vertices = GetVertices(g_vertex_buffer_data, 4 * 8);
	shapeElements.triangles = GetTriangles(shapeElements.vertices, indexes, 6);
	shapeElements.faces = GetFaces(shapeElements.triangles);
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
	sm.UnBind();
	//GeneratePickedShaders();
	shapeState = ShapeState::EXISTING;
}
void Plane::GetSourceLight(glm::vec3 lightSource)
{
	m_sourceLight = lightSource;
}
glm::vec3 Plane::GetNormal()
{
	return normals[0];
}

void Plane::CreateMVPMatrix()
{
	mvp.model = glm::mat4(1.0f);
	mvp.model = glm::translate(mvp.model, glm::vec3(0.0f, 0.0f, -5.0f));
	mvp.model = glm::rotate(mvp.model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	RotateNormals(-90.0f, glm::vec3(1.0f, 0.0f, .0f));
	//mvp.model = glm::scale(mvp.model, glm::vec3(1.0f, 1.0f, 1.0f));

	mvpResult = mvp.proj * mvp.view * mvp.model;
	TranslatePoints(mvp.model, shapeElements.vertices);
	shapeElements.triangles = GetTriangles(shapeElements.vertices, indexes, 6);
	shapeCoords = mvpResult[3];
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
	//UpdatePickedShape();
}


Plane::~Plane()
{
}
