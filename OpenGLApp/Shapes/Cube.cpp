#include "Cube.h"
#include "..\Builders\ShapesBuilder.h"
#include "../Config.h"

Cube::Cube(ShapesBuilder& builder) : Shape(builder)
{
	verts = std::unique_ptr<VerticesShape>(CreateCube());
	unsigned int bufferDataSizes[3] = { 3, 2, 3 };
	Create(verts->Points, verts->Indexes, verts->PointsCount, verts->IndexesCount, bufferDataSizes, 8);
	
	shapeElements.vertices = GetVertices(verts->Points, verts->PointsCount * 8, 8);
	shapeElements.triangles = InitializeTriangles(verts->Indexes, verts->IndexesCount, shapeElements.vertices);
	shapeElements.faces = GetFaces(shapeElements.triangles);
	deffered = true;
	this->ShapeName = "Cube";
}

Cube::Cube(ShapesBuilder&& builder) : Shape(std::move(builder))
{
	verts = std::unique_ptr<VerticesShape>(CreateCube());
	unsigned int bufferDataSizes[3] = { 3, 2, 3 };
	Create(verts->Points, verts->Indexes, verts->PointsCount, verts->IndexesCount, bufferDataSizes, 8);

	shapeElements.vertices = GetVertices(verts->Points, verts->PointsCount * 8, 8);
	shapeElements.triangles = InitializeTriangles(verts->Indexes, verts->IndexesCount, shapeElements.vertices);
	shapeElements.faces = GetFaces(shapeElements.triangles);
	deffered = true;
	this->ShapeName = "Cube";
}


Cube::~Cube()
{

}

void Cube::GenerateTextures(std::vector<Texture*>& textures)
{
	tm.AddTextures(textures);
}

void Cube::CreateMVPMatrix()
{
	mvp.model = glm::mat4(1.0f);
	mvp.model = glm::translate(mvp.model, builder->Pos);
	if(builder->Angle != 0.0f)
		mvp.model = glm::rotate(mvp.model, builder->Angle, builder->Axis);
	TranslatePoints(mvp.model, shapeElements.vertices);
	shapeElements.triangles = InitializeTriangles(verts->Indexes, verts->IndexesCount, shapeElements.vertices);
}


void Cube::Update()
{
	sc.ActivateDefaultProgram();
	sc.EnableUse();
	for (Texture* texture : tm.Textures)
		texture->Bind();
	ShaderTypeGenerator::UpdateModel(sm->shaders, sc.GetCurrentProgram(), mvp.model);
	ShaderTypeGenerator::PassLightMatrixData(sm->shaders, sc.GetCurrentProgram(), functionParams);
	bm->ActivateShapeBufferParts();
}

glm::vec3 Cube::GetNormal()
{
	return glm::vec3();
}

