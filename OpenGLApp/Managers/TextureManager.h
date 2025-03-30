#pragma once
#include <vector>
#include <memory>
#include "..\TextureObjects\Texture.h";
class TextureManager
{
public:
	TextureManager();
	void AddTexture(const char* path);
	void AddTexture(Texture* tex);
	void AddTextures(std::vector<Texture*>& texs);
	void AddTextures(const std::vector<const char*>& texPaths);
	void AddTextures(std::vector<const char*>&& texPaths);
	void DeleteTexture(short int index);
	Texture* GetTexture(short int index);
	void BindTexture(short int index = 0);
	void UnBindTexture(short int index = 0);
	void InitializeTextures();
	void CreateHDRTextures(short int size);
	std::vector<Texture*> Textures;
	~TextureManager();
private:
	unsigned short currentSlot;
	unsigned short mainTexture = 0;
};

