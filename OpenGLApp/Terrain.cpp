#include "Terrain.h"

float* terrainCoordinates;
unsigned int* terrainIndexes;
unsigned int terrainArraySize;
unsigned int indexArraySize;
std::vector<std::array<GLfloat, 8>> coordsContainer;
std::vector<unsigned int> coordsIndexes;
std::vector<GLfloat> coordsData;

Terrain::Terrain()
{
}

Terrain::Terrain(const ShapesBuilder builder) : Shape()
{
	tp = builder.props;
	LoadTerrain();
}

void Terrain::CreateTerrain()
{
	glm::vec3 startPoint = glm::vec3(tp.centerPos.x - ((tp.width / 2.0f) * tp.squareSize),
		tp.centerPos.y,
		tp.centerPos.z - ((tp.height / 2.0f) * tp.squareSize));
	for (int i = 0; i <= tp.width; i++)
	{
		for (int j = 0; j <= tp.height; j++)
		{
			std::array<GLfloat, 8> coords = { startPoint.x + i * tp.squareSize,
			startPoint.y,
			startPoint.z + j * tp.squareSize,
			(float)i,
			(float)j,
			1.0f, 1.0f, 1.0f //to-do count normal
			};
			coordsContainer.push_back(coords);
		}
	}

	for each  (std::array<GLfloat,8> coords  in coordsContainer)
	{
		for each (float data in coords)
		{
			coordsData.push_back(data);
		}
	}
	for (int i = 0; i < coordsContainer.size(); i++)
	{
		if ((i + 1) % (tp.height + 1) == 0 && i != 0)
			continue;
		if ((i + 1) / tp.width == tp.width + 1)
			break;
		coordsIndexes.push_back(i);
		coordsIndexes.push_back(i + tp.height + 1);
		coordsIndexes.push_back(i + tp.height + 2);
		coordsIndexes.push_back(i + 1);
	}

	terrainArraySize = coordsContainer.size();
	indexArraySize = coordsIndexes.size();
}

void Terrain::Update()
{
	sm.Bind();
	for each (Texture * texture in textures)
		texture->Bind();
	mvpResult = mvp.proj * mvp.view * mvp.model;
	shaders[0]->SetUniformMat4f("mvpResult", mvpResult, sm.GetProgram());

	sm.UnBind();
	sm.Bind();
	ib->Bind();
	va->Bind();
}

glm::vec3 Terrain::GetNormal()
{
	return glm::vec3();
}

void Terrain::GenerateShaders()
{
	textures.push_back(new Texture("Images\\TexturesCom_Grass0130_1_seamless_S.jpg", 0, GL_REPEAT));
	shaders.push_back(new Shader("Shaders\\TerrainVertexShader.vert"));
	shaders.push_back(new Shader("Shaders\\TerrainFragmentShader.frag"));
	sm.AddShadersToProgram(shaders);
	sm.Bind();
	CreateMVPMatrix();

	for each (Texture * texture in textures)
		texture->Bind();
	ShaderTypeGenerator::TerrainShaderGenerator(shaders, mvpResult, sm.GetProgram());
	for each (Texture * texture in textures)
		texture->UnBind();
	shapeState = ShapeState::EXISTING;
}

void Terrain::CreateMVPMatrix()
{
	mvp.model = glm::mat4(1.0f);
	mvpResult = mvp.proj * mvp.view * mvp.model;
}

void Terrain::LoadTerrain()
{
	CreateTerrain();
	CreateShape(coordsData.data(), coordsIndexes.data(), terrainArraySize, indexArraySize);
}

Terrain::~Terrain()
{
}
