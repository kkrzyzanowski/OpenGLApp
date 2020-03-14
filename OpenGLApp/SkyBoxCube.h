#pragma once
#include "Shape.h"
#include "CubeMapTexture.h"
#include "ShapesBuilder.h"
class SkyBoxCube :
	public Shape
{
public:
	SkyBoxCube(const ShapesBuilder builder);
	void CreateShape(const GLfloat* points, unsigned int* orederIndex, unsigned int countVertices, unsigned int countIndexes) override;
	void GenerateShaders() override;
	void Update() override;
	void InitializeShapeView(glm::mat4& view);
	glm::vec3 GetNormal() override;
	~SkyBoxCube();
protected:
	CubeMapTexture* cubeMapTexture;
	void CreateMVPMatrix() override;
	std::vector<std::string> paths;
};

