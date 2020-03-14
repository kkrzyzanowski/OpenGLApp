#include "CustomShape.h"

CustomShape::CustomShape(const ShapesBuilder builder)
{
	//stuff with getting model;
	Assimp::Importer importer;
	meshObject = new MeshObject();
	const aiScene* scene = importer.ReadFile(builder.m_path, aiProcess_Triangulate | aiProcess_FlipUVs);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
		return;
	}
	std::string dir = builder.m_path.substr(0, builder.m_path.find_last_of('/'));
	ProcessNode(scene->mRootNode, scene);
	float* vertices = &meshObject->vertices[0];
	unsigned int* indices = &meshObject->indices[0];
	CreateShape(vertices, indices, meshObject->vertices.size() / 8, meshObject->indices.size());
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
		 textures.push_back(tex);
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

void CustomShape::CreateMVPMatrix()
{
	mvp.model = glm::mat4(1.0f);
	insideLightPos = glm::vec3(1.0f, 1.2f, 1.0f);
	mvp.model = glm::translate(mvp.model, insideLightPos);
	mvpResult = mvp.proj * mvp.view * mvp.model;
}

glm::vec3 CustomShape::GetNormal()
{
	return glm::vec3();
}

CustomShape::CustomShape()
{
}


CustomShape::~CustomShape()
{
}

void CustomShape::Update()
{
	sm.Bind();
	for each(Texture* texture in textures)
		texture->Bind();
	mvpResult = mvp.proj * mvp.view * mvp.model;
	shaders[0]->SetUniformMat4f("u_MVP", mvpResult, sm.GetProgram());
	sm.UnBind();
	sm.Bind();
	ib->Bind();
	va->Bind();
}

void CustomShape::GenerateShaders()
{
	shaders.push_back(new Shader("Shaders\\LightDefaultVertexShader.vert"));
	shaders.push_back(new Shader("Shaders\\LightDefaultFragmentShader.frag"));
	sm.AddShadersToProgram(shaders);
	sm.Bind();
	CreateMVPMatrix();
	shaders[0]->SetUniformMat4f("u_MVP", mvpResult, sm.GetProgram());
	shaders[1]->SetUniform4f("u_color", 1.0f, 1.0f, 1.0f, 1.0f, sm.GetProgram());
}
