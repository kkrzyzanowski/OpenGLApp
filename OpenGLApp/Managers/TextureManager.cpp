#include "..\Managers\TextureManager.h"

TextureManager::TextureManager()
{
	currentSlot = 0;
}

void TextureManager::AddTexture(const char* path)
{
	Textures.push_back(new Texture(path, currentSlot));
	++currentSlot;
}

void TextureManager::AddTexture(Texture* tex)
{
	Textures.push_back(tex);
}

void TextureManager::AddTextures(std::vector<Texture*>& texs)
{
	Textures.insert(Textures.end(), texs.begin(), texs.end());
}

void TextureManager::AddTextures(const std::vector<const char*>& texPaths)
{
	for (const char* texturePath : texPaths)
	{
		AddTexture(texturePath);
	}
}

void TextureManager::AddTextures(std::vector<const char*>&& texPaths)
{
	for (const char* texturePath : texPaths)
	{
		AddTexture(texturePath);
	}
}

void TextureManager::DeleteTexture(short int index)
{
	Textures.erase(Textures.begin() + index);
}

Texture* TextureManager::GetTexture(short int index)
{
	return Textures[index];
}

void TextureManager::BindTexture(short int index)
{
	Textures[index]->Bind();
}

void TextureManager::UnBindTexture(short int index)
{
	Textures[index]->UnBind();
}

void TextureManager::InitializeTextures()
{
	for (Texture* tex : Textures)
		tex->CreateTexture();
}

void TextureManager::CreateHDRTextures(short int size)
{
	for (int i = 0; i < size; ++i)
	{
		Texture* tex = new Texture();
		tex->CreateHDRTexture(i);
		Textures.push_back(tex);
	}
}

TextureManager::~TextureManager()
{
}
