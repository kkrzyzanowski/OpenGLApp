#pragma once
#include "Shape.h"
#include "..\CustomProperties.h"

class Terrain : public Shape
{
public:
	Terrain(ShapesBuilder& builder);
	Terrain(ShapesBuilder&& builder);
	void CreateTerrain();
	glm::vec3 GetNormal() override;
	void GenerateShaders() override;
	void ApplyShaders() override;
	void AddParamsToShader() override;
	void LoadTerrain();
	inline glm::vec3* GetSqareOffsets()  { return squareOffsets; };
	inline TerrainProperties& GetTerrainProperties() { return tp; }
	~Terrain();
private:
	void CreateMVPMatrix() override;
	TerrainProperties tp;
	glm::vec3* squareOffsets;
};

