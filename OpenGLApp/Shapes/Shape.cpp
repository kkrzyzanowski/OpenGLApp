#include <algorithm>
#include <time.h>
#include <string>
#include "Shape.h"
#include "..\Builders\ShapesBuilder.h"
#include "../Managers/LightManager.h"

static bool RandomInitializer = false;
//Shape::Shape()
//{
//	shapeState = ShapeState::CREATING;
//	sourceShapeType = SourceShapeType::NO_TYPE;
//	do
//	{
//		this->Id = GenerateId(this->rgbCheck);
//	} while (std::find(shape_ids.begin(), shape_ids.end(), this->Id) != shape_ids.end());
//	sc.ActivateDefaultProgram();
//	Selected = false;
//	bm = new BufferManager();
//	sm = new ShaderManager();
//	
//}

Shape::Shape(ShapesBuilder& builder) : builder(std::make_unique<ShapesBuilder>(std::move(builder)))
{
	Id = GenerateId();
	Selected = false;
	bm = new BufferManager();
	sm = new ShaderManager();
	tm.AddTextures(this->builder->texturePaths);
	sc.ActivateDefaultProgram();
	sm->AddShaders(this->builder->shaderPaths);
}

Shape::Shape(ShapesBuilder&& builder) : builder(std::make_unique<ShapesBuilder>(std::move(builder)))
{
	Id = GenerateId();
	Selected = false;
	bm = new BufferManager();
	sm = new ShaderManager();
	tm.AddTextures(this->builder->texturePaths);
	sc.ActivateDefaultProgram();
	sm->AddShaders(this->builder->shaderPaths);
}

void Shape::Create(const GLfloat* points, unsigned int* orderIndex, unsigned int countVertices, unsigned int countIndexes, unsigned int* bufferDataSizes, unsigned int dataSize)
{
	bm->CreateBuffers(points, orderIndex, countVertices, countIndexes, bufferDataSizes, dataSize);
}

void Shape::Create(const GLfloat* points, std::vector<int>& orderIndex, unsigned int countVertices, unsigned int countIndexes, unsigned int* bufferDataSizes, unsigned int dataSize)
{
	bm->CreateBuffers(points, orderIndex, countVertices, countIndexes, bufferDataSizes, dataSize);
}

const ShaderCompiler Shape::GetShaderCompiler() const
{
	return sc;
}

void Shape::GenerateTextures(std::vector<Texture*>& textures)
{
	tm.AddTextures(textures);
}

void Shape::DeactivateShapeBufferParts()
{
	bm->DeactivateShapeBufferParts();
}

void Shape::Update()
{
	sc.ActivateDefaultProgram();
	sc.EnableUse();
	for (Texture* texture : tm.Textures)
		texture->Bind();
	ShaderTypeGenerator::UpdateModel(sm->shaders, sc.GetCurrentProgram(), mvp.model);
	bm->ActivateShapeBufferParts();
}

void Shape::AfterUpdate()
{
	for (Texture* texture : tm.Textures)
		texture->UnBind();
	sc.DisableUse();
}

void Shape::ActivateShapeBufferParts()
{
	bm->ActivateShapeBufferParts();
}
void Shape::ApplyShapeView(const glm::mat4& view)
{
	this->mvp.view = view;
}
void Shape::GenerateShaders()
{
	sc.ActivateDefaultProgram();
	sc.AddShadersToProgram(sm->shaders);
	sc.EnableUse();
	PrepareShaderMatricesFieldData();
	CreateMVPMatrix();
	AddParamsToShader();

	shapeState = ShapeState::EXISTING;
}
void Shape::ApplyShaders()
{
	for (Texture* texture : tm.Textures)
		texture->Bind();
	sm->AddShaderFunction(builder->Func, functionParams);
	sm->ExecuteShaderFunction(sm->shaders, sc.GetCurrentProgram());
	for (Texture* texture : tm.Textures)
		texture->UnBind();
}
void Shape::GenerateVertices()
{
	// TO-DO for all shapes
}
const glm::vec3 Shape::GetShapeCenterPoint() const
{
	return shapeCoords;
}
void Shape::ApplyProjectionMatrix(glm::mat4 proj)
{
	this->mvp.proj = proj;
}
void Shape::SetMainLight(const glm::vec3& light)
{
	mainLight = light;
}

void Shape::SetEyeCamPos(const glm::vec3& pos)
{
	camEyePos = pos;
}
const SourceShapeType Shape::GetSourceShapeType() const
{
	return builder->Type;
}

void Shape::RotateNormals(float rotation, glm::vec3 rotationAxis)
{
	for (glm::vec3& normal : normals)
	{
		normal = glm::rotate(normal, glm::radians(rotation), rotationAxis);
		std::cout << "Normal x: " << normal.x << " Normal y: " << normal.y << " Normal z: "
			<< normal.z << std::endl;
	}
}
void Shape::Translate(const glm::vec3& valueToMove)
{
	glm::mat4 translationMatrix = glm::mat4(1.0f);
	translationMatrix = glm::translate(translationMatrix, valueToMove);
	mvp.model = translationMatrix * mvp.model;
	TranslatePoints(translationMatrix, shapeElements.vertices);
	shapeElements.triangles = InitializeTriangles(verts->Indexes, verts->IndexesCount, shapeElements.vertices);
}

void Shape::SetPosition(const glm::vec3& pos)
{
	glm::vec4 previousPos = mvp.model[3];
	glm::mat4 deltaModel = mvp.model;
	mvp.model[3][0] = pos.x;
	mvp.model[3][1] = pos.y;
	mvp.model[3][2] = pos.z;
}
void Shape::Scale(float value)
{
}
void Shape::Rotate(float value)
{
}

void Shape::PassShaderParams(std::vector<ShaderParams> params)
{
	functionParams.insert(functionParams.end(), params.begin(), params.end());
}

ShapeState Shape::GetCreationState() const
{
	return shapeState;
}
glm::vec3 Shape::GetPosition()
{
	return glm::vec3(mvp.model[3]);
}

ShapeType Shape::GetType()
{
	return ShapeType();
}



void Shape::InitializePickedShape()
{
	if (stencilOutline != nullptr)
	{
		stencilOutline = new StencilOutline();
	}

	stencilOutline->InitializePerspective(this->mvp.proj);
	stencilOutline->InitializeView(this->mvp.view);
	stencilOutline->InitializeModel(this->mvp.model);
	stencilOutline->SetColor();
	stencilOutline->BindMVMatrices();
	stencilOutline->UseShader();
}
void Shape::UpdatePickedShape()
{
	stencilOutline->UpdateModel(mvp.model);
	stencilOutline->Update();
	bm->ActivateShapeBufferParts();
}

Shape::~Shape()
{
	delete light;
	delete bm;
	delete sm;

	for (Texture* tex : tm.Textures)
		delete tex;
	for (Shader* shader : sm->shaders)
		delete shader;
	for (Shader* pickedShader : sm->pickedShaders)
		delete pickedShader;
}

void Shape::CreateType()
{
	switch (builder->Type)
	{
	case SourceShapeType::SHAPE:
	{
		type = new DiffuseShape();
		break;
	}
	case SourceShapeType::LIGHT:
	{
		type = new LightShape();
		break;
	}
	case SourceShapeType::PARTICLE:
	{
		type = new ParticleShape();
		break;
	}
	default:
		break;
	}
}

unsigned long GenerateId()
{
	const int size = 8;
	const int idSize = 24;
	RGB rgb{};

	if (!RandomInitializer)
	{
		srand(time(NULL));
		RandomInitializer = true;
	}

	rgb.r = rand() % 255;
	rgb.g = rand() % 255;
	rgb.b = rand() % 255;

	std::string id = std::to_string(rgb.r) + std::to_string(rgb.g) + std::to_string(rgb.b);

	return std::stol(id);

}


std::vector<std::vector<std::array<glm::vec3, 3>>> Shape::GetFaces(std::vector<std::array<glm::vec3, 3>>& triangles)
{
	std::vector<std::vector<std::array<glm::vec3, 3>>> faces;
	std::vector<std::array<glm::vec3, 3>> triangleUnused;
	for (std::array<glm::vec3, 3> triangle : triangles)
	{
		bool match = false;
		size_t matchedIndex = 0;
		for (std::array<glm::vec3, 3> ut : triangleUnused)
		{
			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					for (int k = 0, vertexMatch = 0; k < 3; k++)
					{
						if (triangle[i][k] == ut[j][k])
						{
							vertexMatch++;
							if (vertexMatch > 1 && triangle[i] != ut[j])
							{
								match = true;
								std::vector <std::array<glm::vec3, 3>> face = { triangle, ut };
								faces.push_back(face);
								std::vector<std::array<glm::vec3, 3>>::iterator itr = std::find(triangleUnused.begin(), triangleUnused.end(), ut);
								matchedIndex = std::distance(triangleUnused.begin(), itr);
								break;
							}

						}
					}
					if (match)
						break;
				}
				if (match)
					break;
			}
			if (match)
			{
				triangleUnused.erase(triangleUnused.begin() + matchedIndex);
				matchedIndex = 0;
				break;
			}
		}
		if (!match)
			triangleUnused.push_back(triangle);
		else
			match = false;
	}
	return faces;
}

std::vector<std::array<glm::vec3, 3>> Shape::InitializeTriangles(size_t* indices, int indices_count, Vertices& vertices)
{
	std::vector<std::array<glm::vec3, 3>> triangles;

	for (int i = 0; i < indices_count; i += 3)
	{
		std::array<glm::vec3, 3> vertex = { vertices[indices[i]], vertices[indices[i + 1]], vertices[indices[i + 2]] };
		triangles.push_back(vertex);
	}
	return triangles;
}

std::vector<std::array<glm::vec3, 3>> Shape::InitializeTriangles(std::vector<int>& indices, Vertices& vertices)
{
	std::vector<std::array<glm::vec3, 3>> triangles;
	for (int i = 0; i < indices.size(); i += 3)
	{
		std::array<glm::vec3, 3> vertex = { vertices[indices[i]], vertices[indices[i + 1]], vertices[indices[i + 2]] };
		triangles.push_back(vertex);
	}
	return triangles;
}


std::vector<glm::vec3> Shape::GetVertices(GLfloat* objectData, size_t elements, unsigned int bufferSize)
{
	std::vector<glm::vec3> vertices;
	for (int i = 0; i < elements; i += bufferSize)
	{
		vertices.push_back(glm::vec3(objectData[i], objectData[i + 1], objectData[i + 2]));
	}
	return vertices;
}


std::vector<std::array<glm::vec3, 2>> Shape::GetEdges(GLfloat* objectData)
{
	std::vector<std::array<glm::vec3, 2>> edges;
	int elements = *(&objectData + 1) - objectData; // getting size of array
	std::vector<glm::vec3> vertices;
	for (int i = 0, steps = 0; i < elements; i + 8, steps++)
	{
		glm::vec3 vertex = { objectData[i], objectData[i + 1], objectData[i + 2] };
		vertices.push_back(vertex);
		if (steps == 2)
		{
			glm::vec3 previousVertex;
			bool axisRepeat[3] = { true, true, true };
			for (int j = 0; j < vertices.size(); j++)
			{
				if (j == 0)
				{
					previousVertex = vertices[j];
					continue;
				}
				if (vertices[j].x != previousVertex.x)
				{
					axisRepeat[0] = false;
				}
				if (vertices[j].y != previousVertex.y)
				{
					axisRepeat[1] = false;
				}
				if (vertices[j].z != previousVertex.z)
				{
					axisRepeat[2] = false;
				}
			}
			for (int j = 0; j < 3; j++)
			{
				if (!axisRepeat[j])
				{
					if (vertices[j][j] == vertices[j + 1][j])
					{
						edges.push_back(std::array<glm::vec3, 2>({ vertices[j], vertices[j + 1] }));
						break;
					}
					else
					{
						edges.push_back(std::array<glm::vec3, 2>({ vertices[j], vertices[j + 2] }));
						break;
					}
				}
			}
			steps = 0;
		}
	}
	return edges;
}

void Shape::TranslatePoints(glm::mat4& model, Vertices& verts)
{
	for (auto iterator = verts.begin(); iterator != verts.end(); iterator++)
	{
		glm::vec4 point4f = glm::vec4(iterator->x, iterator->y, iterator->z, 1.0f);
		point4f = model * point4f;
		iterator->x = point4f.x;
		iterator->y = point4f.y;
		iterator->z = point4f.z;
	}
}


Triangles Shape::GetTriangles() const
{
	return shapeElements.triangles;
}

void Shape::GenerateShadow(glm::mat4& lightSpaceMatrix)
{

}

void Shape::UpdateLight()
{
	/*if (shadow)
	{
		sc.ActivateProgram("shadows");
		sc.EnableUse();
		ShaderTypeGenerator::UpdateModel(sm->shadowShaders, sc.GetCurrentProgram(), mvp.model);
		sc.DisableUse();
		sc.ActivateDefaultProgram();
	}*/
}

void Shape::AddParamsToShader()
{
	switch (builder->ShadingType)
	{
	case Shading::DEFFERED_SHADING:
	{
		functionParams.push_back(mvp.model);
		break;
	}
	case Shading::FORWARD_SHADING:
	case Shading::DISPLACEMENT:
	{
		functionParams.push_back(mvp.model);
		functionParams.push_back(mainLight);
		break;
	}
	case Shading::ONLY_COLOR:
	{
		functionParams.push_back(builder->color);
		break;
	}
	case Shading::TEXTURE_COLOR:
	{
		functionParams.push_back(mvp.model);
		functionParams.push_back(builder->color);
		functionParams.push_back((unsigned short)0);
		break;
	}
	case Shading::HDR_SHADING:
	{
		functionParams.push_back(mvp.model);
		break;
	}
	default:
		functionParams.push_back(mvp.model);
		break;
	}

}


Shading Shape::GetShading() const
{
	return builder->ShadingType;
};

bool Shape::IsShadowTurnOn() const
{
	return builder->IsShadowActive;
}

bool Shape::IsHDROn() const
{
	return builder->HDR;
}

void Shape::PrepareShaderMatricesFieldData()
{
	sc.BindBlockData("Matrices");
}

