#pragma once
#include "Shape.h"
#include "..\Builders\ShapesBuilder.h"
#include "..\TextureObjects\CubeMapTexture.h"
class SkyBoxCube :
	public Shape
{
public:
	SkyBoxCube(ShapesBuilder& builder);
	SkyBoxCube(ShapesBuilder&& builder);
	void Create(const GLfloat* points, unsigned int* orederIndex, unsigned int countVertices, unsigned int countIndexes, unsigned int* bufferDataSizes, unsigned int dataSize) override;
	void GenerateShaders() override;
	void ApplyShaders() override;
	void AfterUpdate() override;
	void Update() override;
	void InitializeShapeView(glm::mat4& view);
	glm::vec3 GetNormal() override;
	~SkyBoxCube();
protected:
	CubeMapTexture* cubeMapTexture;
	void CreateMVPMatrix() override;
	std::vector<std::string> paths;
};

