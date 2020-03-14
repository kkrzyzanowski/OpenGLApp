#pragma once
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <vector>
#include "Shape.h"
#include "ShapesBuilder.h"
struct MeshObject
{
	std::vector<float> vertices;
	std::vector<unsigned int> indices;
};

class CustomShape :
	public Shape
{
public:
	CustomShape();
	CustomShape::CustomShape(const ShapesBuilder builder);
	//void CreateShape(const GLfloat* points, unsigned int* orderIndex, unsigned int countVertices) override;
	void Update() override;
	void GenerateShaders() override;
	~CustomShape();
private:
	MeshObject* meshObject;
	void GetBufferVertices(aiMesh* mesh, const aiScene* scene);
	void GetBufferIndices(aiMesh* mesh, const aiScene* scene);
	void SetMaterials(aiMesh* mesh, const aiScene* scene, aiTextureType type);
	void SetTextures(aiMaterial* mat, aiTextureType type);
	void ProcessNode(aiNode* node, const aiScene* scene);
	void CreateMVPMatrix() override;
	glm::vec3 GetNormal() override;
};

struct Vertex
{
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
};
