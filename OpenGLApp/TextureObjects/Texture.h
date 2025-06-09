#pragma once
#include <GL/glew.h>
#include <string>
#include "Stb_image_reader.h"

enum TextureMode
{
	TEXTURE, FRAMEBUFFER, SHADOWMAP, HDR_TEXTURE
};

class Texture
{
public:
	Texture(const std::string& path, unsigned int slot, int mode = GL_CLAMP_TO_EDGE);
	Texture(unsigned int slot = 0, unsigned short colorAttachment = 0, int colorMode = GL_FLOAT, TextureMode textureMode = TextureMode::TEXTURE);
	~Texture();
	void Bind(unsigned short slot) const;
	virtual void Bind() const;
	void BindNoActive() const;
	virtual void UnBind() const;

	void CreateTexture();
	void CreateFrameBufferTexture();

	void CreateShadowMapTexture();

	void CreateHDRTexture();

	void CreateTextureForFrameBuffer();

	inline int GetWidth() const { return m_width; }
	inline int GetHeight() const { return m_height; }
	inline unsigned int GetTextureID() const { return m_TextureID; }
	inline unsigned int GetDepthTextureID() const { return m_DepthTextureID; }
	inline std::string GetTextureName() const { return name; }
	inline bool CanBeActive() const { return canBeActive; }
	inline void SetActive(bool active) { canBeActive = active; }
	unsigned int Slot;
protected:
	int m_width;
	int m_height;
	int m_BPP;
	std::string m_path;
	unsigned int m_TextureID;
	unsigned int m_DepthTextureID;
	std::string name;
	unsigned char* m_localBuffer;
	TextureMode m_mode;
	unsigned short m_colorAttachment;
	unsigned short m_dataType;
	bool canBeActive;
private:
	
};

