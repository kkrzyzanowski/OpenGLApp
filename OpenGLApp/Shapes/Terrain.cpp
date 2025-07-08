#include "Terrain.h"
#include "..\Builders\ShapesBuilder.h"
#include "..\Managers\BitManager.h"

float* terrainCoordinates;
unsigned int* terrainIndexes;
unsigned int terrainArraySize;
unsigned int indexArraySize;
std::vector<std::array<GLfloat, 8>> coordsContainer;
std::vector<unsigned int> coordsIndexes;
std::vector<GLfloat> coordsData;

Terrain::Terrain(ShapesBuilder& builder) : Shape(builder)
{
	ShapeName = "Terrain";
	tp = builder._props;
	unsigned int count = tp.width * tp.height;
	squareOffsets = new glm::vec3[count];
	LoadTerrain();
}

Terrain::Terrain(ShapesBuilder&& builder) : Shape(std::move(builder))
{
	ShapeName = "Terrain";
	tp = builder._props;
	unsigned int count = tp.width * tp.height;
	squareOffsets = new glm::vec3[count];
	LoadTerrain();
}

void Terrain::CreateTerrain()
{
	std::vector<glm::vec3> terrainPoints;
	glm::vec3 pointLeftUp = glm::vec3(tp.centerPos.x - ((tp.width / 2.0f) * tp.squareSize),
		tp.centerPos.y,
		tp.centerPos.z - ((tp.height / 2.0f) * tp.squareSize));
	glm::vec3 pointLeftDown = glm::vec3(pointLeftUp.x, pointLeftUp.y, pointLeftUp.z + tp.squareSize);
	glm::vec3 pointRightUp = glm::vec3(pointLeftUp.x + tp.squareSize, pointLeftUp.y, pointLeftUp.z);
	glm::vec3 pointRightDow = glm::vec3(pointLeftUp.x + tp.squareSize, pointLeftUp.y, pointLeftUp.z + tp.squareSize);
	terrainPoints.insert(terrainPoints.end(), { pointLeftUp, pointLeftDown, pointRightUp, pointRightDow });
	for (int i = 0, instanceNumber = 0; i < tp.width; ++i)
	{
		for (int j = 0; j < tp.height; ++j)
		{
			squareOffsets[instanceNumber].x = i * tp.squareSize;
			squareOffsets[instanceNumber].y = 0.0f;
			squareOffsets[instanceNumber++].z = j * tp.squareSize;
		}
	}
	BitManager* bm = new BitManager();
	for (int i = 0; i < terrainPoints.size(); i++)
	{
		std::array<GLfloat, 8> coords = { terrainPoints[i].x,
			terrainPoints[i].y,
			terrainPoints[i].z,
			(float)bm->GetBitFromInteger(0, i),
			(float)bm->GetBitFromInteger(1, i),
			0.0f, 1.0f, 0.0f //to-do count normal
		};
		coordsContainer.push_back(coords);
	}

	for (std::array<GLfloat, 8> coords : coordsContainer)
	{
		for (float data : coords)
		{
			coordsData.push_back(data);
		}
	}
	coordsIndexes.insert(coordsIndexes.begin(), { 0 ,1, 2, 3 });


	terrainArraySize = coordsContainer.size();
	indexArraySize = coordsIndexes.size();
	delete bm;
}

glm::vec3 Terrain::GetNormal()
{
	return glm::vec3();
}

void Terrain::GenerateShaders()
{
	sc.ActivateDefaultProgram();
	sc.AddShadersToProgram(sm->shaders);
	sc.EnableUse();
	PrepareShaderMatricesFieldData();
	AddParamsToShader();
	CreateMVPMatrix();
	
	shapeState = ShapeState::EXISTING;
}

void Terrain::ApplyShaders()
{
	for (unsigned int i = 0; i < tp.width * tp.height; i++)
	{
		for (Texture* texture : tm.Textures)
			texture->Bind();
		functionParams[2] = squareOffsets[i];
		functionParams[3] = i;
		ShaderTypeGenerator::InstancedTerrainShaderGenerator(sm->shaders, sc.GetDefaultProgram(), functionParams);
		for (Texture* texture : tm.Textures)
			texture->UnBind();
	}
	sc.DisableUse();
}

void Terrain::AddParamsToShader()
{
	functionParams.push_back(mvp.model);
	functionParams.push_back(mainLight);
	functionParams.push_back(squareOffsets[0]);
	functionParams.push_back(unsigned int(0));
}

void Terrain::CreateMVPMatrix()
{
	mvp.model = glm::mat4(1.0f);
	mvp.model = glm::translate(mvp.model, builder->Pos);
}

void Terrain::LoadTerrain()
{
	CreateTerrain();
	Create(coordsData.data(), coordsIndexes.data(), terrainArraySize, indexArraySize, new unsigned int[] { 3, 2, 3 }, 8);
}

Terrain::~Terrain()
{
	delete[] squareOffsets;
}
