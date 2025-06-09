#include "Plane.h"
#include <iostream>
#include "..\Builders\ShapesBuilder.h"

std::vector<glm::vec3> planeDefaultNormals = { glm::vec3(0.0f, 1.0f, 0.0f),
									glm::vec3(0.0f, 1.0f, 0.0f),
									glm::vec3(0.0f, 1.0f, 0.0f),
									glm::vec3(0.0f, 1.0f, 0.0f) };


Plane::Plane(ShapesBuilder& builder): Shape(builder)
{
	GenerateVertices();
	shapeParams.normals = normals = planeDefaultNormals;
	light = builder._light;

	ShapeName = "Plane";
	verts = std::unique_ptr<VerticesShape>(CreatePlane());
	unsigned int bufferDataSizes[5] = { 3, 2, 3, 3, 3};
	Create(verts->Points, verts->Indexes , verts->PointsCount, verts->IndexesCount, bufferDataSizes, 14);
	shapeElements.vertices = GetVertices(verts->Points, verts->PointsCount * 14, 14);
	shapeElements.triangles = InitializeTriangles(verts->Indexes, verts->IndexesCount, shapeElements.vertices);
	shapeElements.faces = GetFaces(shapeElements.triangles);
	CreateType();
}

Plane::Plane(ShapesBuilder&& builder) : Shape(std::move(builder))
{
	GenerateVertices();
	shapeParams.normals = normals = planeDefaultNormals;
	light = builder._light;

	ShapeName = "Plane";
	verts = std::unique_ptr<VerticesShape>(CreatePlane());
	unsigned int bufferDataSizes[5] = { 3, 2, 3, 3, 3 };
	Create(verts->Points, verts->Indexes, verts->PointsCount, verts->IndexesCount, bufferDataSizes, 14);
	shapeElements.vertices = GetVertices(verts->Points, verts->PointsCount * 14, 14);
	shapeElements.triangles = InitializeTriangles(verts->Indexes, verts->IndexesCount, shapeElements.vertices);
	shapeElements.faces = GetFaces(shapeElements.triangles);
	CreateType();
}

void Plane::GetSourceLight(glm::vec3 lightSource)
{
	m_sourceLight = lightSource;
}
void Plane::Translate(const glm::vec3& valueToMove)
{
	Shape::Translate(valueToMove);
}
glm::vec3 Plane::GetNormal()
{
	return normals[0];
}

void Plane::CreateMVPMatrix()
{
	mvp.model = glm::mat4(1.0f);
	mvp.model = glm::translate(mvp.model, builder->Pos);
	mvp.model = glm::scale(mvp.model, builder->ScaleVector);
	if(builder->Angle != 0.0f)
		mvp.model = glm::rotate(mvp.model, glm::radians(builder->Angle), builder->Axis);
	mvp.model = glm::scale(mvp.model, builder->ScaleVector);
	TranslatePoints(mvp.model, shapeElements.vertices);
	shapeElements.triangles = InitializeTriangles(verts->Indexes, verts->IndexesCount, shapeElements.vertices);
}

void Plane::Update()
{
	sc.ActivateDefaultProgram();
	sc.EnableUse();
	for (Texture* texture : tm.Textures)
		texture->Bind();
	ShaderTypeGenerator::UpdateModel(sm->shaders, sc.GetCurrentProgram(), mvp.model);
	bm->BindBuffers();
}

Plane::~Plane()
{

}
