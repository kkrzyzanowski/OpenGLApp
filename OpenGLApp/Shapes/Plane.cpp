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
void Plane::Translate()
{
	Shape::Translate();
}
glm::vec3 Plane::GetNormal()
{
	return normals[0];
}

Plane::~Plane()
{

}
