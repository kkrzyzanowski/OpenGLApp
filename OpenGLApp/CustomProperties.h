#pragma once
#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"

struct CustomProperties
{

};

struct TerrainProperties
{
	float heightTerrain{ 0.0f };
	float squareSize{ 1.0f };
	unsigned int height;
	unsigned int width;
	glm::vec3 centerPos;
};