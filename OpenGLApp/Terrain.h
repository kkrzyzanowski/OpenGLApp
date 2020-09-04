#pragma once
#include "Shape.h"
#include "ShapesBuilder.h"
#include "CustomProperties.h"

class Terrain : public Shape
{
public:
	Terrain();
	Terrain(const ShapesBuilder builder);
	void CreateTerrain();
	void Update() override;
	glm::vec3 GetNormal() override;
	void GenerateShaders() override;
	void LoadTerrain();
	~Terrain();
private:
	void CreateMVPMatrix() override;
	TerrainProperties tp;
	
};

