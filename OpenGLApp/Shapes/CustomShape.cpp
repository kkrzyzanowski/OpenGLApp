#include "CustomShape.h"
#include "..\Builders\ShapesBuilder.h"

CustomShape::CustomShape(ShapesBuilder& builder): Shape(builder)
{
	//stuff with getting model;
	Assimp::Importer importer;
	meshObject = new MeshObject();
	const aiScene* scene = importer.ReadFile(this->builder->_path, aiProcess_Triangulate | aiProcess_FlipWindingOrder
		| aiProcess_FlipUVs);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
		return;
	}
	std::string dir = this->builder->_path.substr(0, this->builder->_path.find_last_of('/'));
	ProcessNode(scene->mRootNode, scene);
	float* vertices = &meshObject->vertices[0];
	unsigned int* indices = &meshObject->indices[0];
	unsigned int bufferDataSizes[3] = { 3, 2, 3 };
	Create(vertices, indices, meshObject->vertices.size() / 8, meshObject->indices.size(), bufferDataSizes, 8);
	InitializeShapeElements();
	ShapeName = "Custom";
}

CustomShape::CustomShape(ShapesBuilder&& builder) : Shape(std::move(builder)) 
{
	//stuff with getting model;	
	Assimp::Importer importer;
	meshObject = new MeshObject();
	const aiScene* scene = importer.ReadFile(this->builder->_path, aiProcess_Triangulate | aiProcess_FlipUVs);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
		return;
	}
	std::string dir = this->builder->_path.substr(0, this->builder->_path.find_last_of('/'));
	ProcessNode(scene->mRootNode, scene);
	float* vertices = &meshObject->vertices[0];
	unsigned int* indices = &meshObject->indices[0];
	unsigned int bufferDataSizes[3] = { 3, 2, 3 };
	Create(vertices, indices, meshObject->vertices.size() / 8, meshObject->indices.size(), bufferDataSizes, 8);
	InitializeShapeElements();
	ShapeName = "Custom";
}

void CustomShape::GetBufferVertices(aiMesh * mesh, const aiScene * scene)
{
	std::vector<float> bufferData;
	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		bufferData.push_back(mesh->mVertices[i].x);
		bufferData.push_back(mesh->mVertices[i].y);
		bufferData.push_back(mesh->mVertices[i].z);
		if (mesh->mTextureCoords[0])
		{
			bufferData.push_back(mesh->mTextureCoords[0][i].x);
			bufferData.push_back(mesh->mTextureCoords[0][i].y);
		}
		else
		{
			bufferData.push_back(0.0f);
			bufferData.push_back(0.0f);
		}
		//vert.Position = vec;
		//vertices.push_back(vert);
		bufferData.push_back(mesh->mNormals[i].x);
		bufferData.push_back(mesh->mNormals[i].y);
		bufferData.push_back(mesh->mNormals[i].z);
	}
	meshObject->vertices.insert(meshObject->vertices.end(), bufferData.begin(), bufferData.end());
}

void CustomShape::GetBufferIndices(aiMesh * mesh, const aiScene * scene)
{
	 std::vector<unsigned int> bufferData;
	 for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	 {
		 aiFace face = mesh->mFaces[i];
		 for (unsigned int j = 0; j < face.mNumIndices; j++)
		 {
			 bufferData.push_back(face.mIndices[j]);
		 }
	 }
	 meshObject->indices.insert(meshObject->indices.end(), bufferData.begin(), bufferData.end());
}

void CustomShape::InitializeShapeElements()
{
	verts = std::unique_ptr<VerticesShape>(new VerticesShape());
	verts->Points = &meshObject->vertices[0];
	verts->Indexes = &meshObject->indices[0];
	verts->PointsCount = meshObject->vertices.size() / 8;
	verts->IndexesCount = meshObject->indices.size();
	shapeElements.vertices = GetVertices(&meshObject->vertices[0], meshObject->vertices.size(), 8);
	shapeElements.triangles = InitializeTriangles(&meshObject->indices[0], meshObject->indices.size(), shapeElements.vertices);
}


void CustomShape::SetMaterials(aiMesh * mesh, const aiScene * scene, aiTextureType type)
{
	if (mesh->mMaterialIndex >= 0)
	{
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
		SetTextures(material, type);
	}
}

void CustomShape::SetTextures(aiMaterial * mat, aiTextureType type)
{
	 for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
	 {
		 aiString str;
		 mat->GetTexture(type, i, &str);
		 Texture* tex = new Texture(str.C_Str(), i);
		 tm.Textures.push_back(tex);
	 }
	 
}

void CustomShape::ProcessNode(aiNode* node, const aiScene* scene)
{
	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
		GetBufferVertices(mesh, scene);
		GetBufferIndices(mesh, scene);
	}
	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		ProcessNode(node->mChildren[i], scene);
	}
}

glm::vec3 CustomShape::GetNormal()
{
	return glm::vec3();
}



CustomShape::~CustomShape()
{
}



