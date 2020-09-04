#pragma once
#include "Renderer.h"
#include "ImageLoader\stb_image.h"

enum TextureMode
{
	TEXTURE, FRAMEBUFFER
};

class Texture
{
public:
	Texture(const std::string& path, unsigned int slot, int mode = GL_CLAMP_TO_EDGE);
	Texture();
	~Texture();
	virtual void Bind() const;
	virtual void UnBind() const;

	void CreateFrameBufferTexture();

	inline int GetWidth() const { return m_width; }
	inline int GetHeight() const { return m_height; }
 unsigned int GetTextureID() { return m_TextureID; }
	 unsigned int GetDepthTextureID()  { return m_DepthTextureID; }
	inline std::string GetTextureName() const { return name; }
protected:
	int m_width;
	int m_height;
	int m_BPP;
	std::string m_path;
	unsigned int m_TextureID;
	unsigned int m_DepthTextureID;
	std::string name;
	unsigned char* m_localBuffer;
	unsigned int m_slot;
	TextureMode mode;

private:
	
};

