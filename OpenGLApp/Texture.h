#pragma once
#include "Renderer.h"
#include "ImageLoader\stb_image.h"

class Texture
{
public:
	Texture(const std::string& path, unsigned int slot);
	Texture();
	~Texture();
	virtual void Bind() const;
	virtual void UnBind() const;

	inline int GetWidth() const { return m_width; }
	inline int GetHeight() const { return m_height; }
	inline unsigned int GetTextureID() const { return m_TextureID; }
	inline std::string GetTextureName() const { return name; }
protected:
	int m_width;
	int m_height;
	int m_BPP;
	std::string m_path;
	unsigned int m_TextureID;
	std::string name;
	unsigned char* m_localBuffer;
	unsigned int m_slot;

private:
	
};

