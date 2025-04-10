//#define GLM_ENABLE_EXPERIMENTAL
#include "Sphere.h"
#include "..\Builders\ShapesBuilder.h"
#include "..\glm\gtx\rotate_vector.hpp"

int sectors = 24;
int rings = 12;
int pointsCount = sectors * rings * (3 + 2 + 3);
int indexesValue = (rings-1) * (sectors) * 6;

Sphere::Sphere( ShapesBuilder& builder) : Shape(builder)
{
	light = builder._light;
	verts = std::unique_ptr<VerticesShape>(CreateSphere(rings, sectors, 8));
	physics = { 1.0f, glm::vec3(0.0f, -.01f, 0.0f),
		1.0f, 0.0f, true, glm::vec3(.0f, 10.0f, .0f) };
	unsigned int bufferDataSizes[3] = { 3, 2, 3 };
	Create(verts->Points, verts->Indexes, verts->PointsCount, verts->IndexesCount, bufferDataSizes, 8);
	shapeElements.vertices = GetVertices(verts->Points, verts->PointsCount * 8, 8);
	shapeElements.triangles = InitializeTriangles(verts->Indexes, verts->IndexesCount, shapeElements.vertices);
	shapeElements.faces = GetFaces(shapeElements.triangles);
	CreateType();
	ShapeName = "Sphere";
}

Sphere::Sphere(ShapesBuilder&& builder) : Shape(std::move(builder))
{
	light = builder._light;
	verts = std::unique_ptr<VerticesShape>(CreateSphere(rings, sectors, 8));
	physics = { 1.0f, glm::vec3(0.0f, -.01f, 0.0f),
		1.0f, 0.0f, true, glm::vec3(.0f, 10.0f, .0f) };
	unsigned int bufferDataSizes[3] = { 3, 2, 3 };
	Create(verts->Points, verts->Indexes, verts->PointsCount, verts->IndexesCount, bufferDataSizes, 8);
	shapeElements.vertices = GetVertices(verts->Points, verts->PointsCount * 8, 8);
	shapeElements.triangles = InitializeTriangles(verts->Indexes, verts->IndexesCount, shapeElements.vertices);
	shapeElements.faces = GetFaces(shapeElements.triangles);
	CreateType();
	ShapeName = "Sphere";
}


void Sphere::Update()
{
	sc.EnableUse();
	for(Texture* texture: tm.Textures)
		texture->Bind();
	ShaderTypeGenerator::UpdateModel(sm->shaders, sc.GetDefaultProgram(), mvp.model);
	bm->ActivateShapeBufferParts();
}


void Sphere::CreateMVPMatrix()
{
	mvp.model = glm::mat4(1.0f);
	mvp.model = glm::translate(mvp.model, builder->Pos);
	if(builder->Angle != 0.0f)
		mvp.model = glm::rotate(mvp.model, builder->Angle, builder->Axis);
	TranslatePoints(mvp.model, shapeElements.vertices);
	shapeElements.triangles = InitializeTriangles(verts->Indexes, verts->IndexesCount, shapeElements.vertices);
}


glm::vec3 Sphere::GetNormal()
{
	return glm::vec3();
}

float Sphere::GetRadius() const
{
	return radius;
}


Sphere::~Sphere()
{
}