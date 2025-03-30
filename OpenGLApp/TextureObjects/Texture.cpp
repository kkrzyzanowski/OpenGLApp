#include "Texture.h"
#include "..\Config.h"
#include "..\Rendering\Renderer.h"

Texture::Texture(const std::string& path, unsigned int slot, int mode) : m_path(path), Slot(slot), m_TextureID(0), m_localBuffer(nullptr),
m_width(0), m_height(0), m_BPP(0), canBeActive(true)
{
	//stbi_set_flip_vertically_on_load(1);

	name = path.substr(path.find_last_of('/\\') + 1);
	name = path.substr(0, path.find_last_of('.'));
	m_localBuffer = stbi_load(path.c_str(), &m_width, &m_height, &m_BPP, 4);
	GLCall(glGenTextures(1, &m_TextureID));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_TextureID));

	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, mode));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, mode));

	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_localBuffer));
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
	if (m_localBuffer)
		stbi_image_free(m_localBuffer);
}

Texture::Texture(unsigned int slot, unsigned short colorAttachment, int dataType, TextureMode textureMode) : m_path(""), Slot(slot), m_TextureID(0), m_localBuffer(nullptr),
m_width(0), m_height(0), m_BPP(0), m_colorAttachment(colorAttachment), m_dataType(dataType), m_mode(textureMode), canBeActive(true)
{
	
}

Texture::~Texture()
{
	GLCall(glDeleteTextures(1, &m_TextureID));
}

void Texture::BindTexture(unsigned short slot) const
{
	GLCall(glActiveTexture(GL_TEXTURE0 + slot));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_TextureID));
}

void Texture::Bind() const
{
	if (canBeActive)
	{
		GLCall(glActiveTexture(GL_TEXTURE0 + Slot));
		GLCall(glBindTexture(GL_TEXTURE_2D, m_TextureID));
	}
}

void Texture::UnBind() const
{
	GLCall(glActiveTexture(GL_TEXTURE0 + Slot));
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}

void Texture::CreateTexture()
{
	switch (m_mode)
	{
	case TextureMode::TEXTURE:
	{
		break;
	}
	case TextureMode::FRAMEBUFFER:
	{
		m_width = SCREEN_WIDTH;
		m_height = SCREEN_HEIGHT;
		CreateFrameBufferTexture();
		break;
	}
	case TextureMode::SHADOWMAP:
	{
		m_width = SHADOW_WIDTH;
		m_height = SHADOW_HEIGHT;
		CreateShadowMapTexture();
		break;
	}
	case TextureMode::HDR_TEXTURE:
	{
		m_width = SHADOW_WIDTH;
		m_height = SHADOW_HEIGHT;
		CreateHDRTexture(m_colorAttachment);
		break;
	}
	}
}

void Texture::CreateFrameBufferTexture()
{
	glGenTextures(1, &m_TextureID);
	glBindTexture(GL_TEXTURE_2D, m_TextureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, SCREEN_WIDTH, SCREEN_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, m_TextureID, 0);

	GLenum DrawBuffers[1] = { GL_COLOR_ATTACHMENT0 };
	glDrawBuffers(1, DrawBuffers); // "1" is the size of DrawBuffers
}

void Texture::CreateShadowMapTexture()
{
	m_width = SHADOW_WIDTH;
	m_height = SHADOW_HEIGHT;

	///temporary last slot on textures
	Slot = 7;
	///
	glGenTextures(1, &m_TextureID);
	glBindTexture(GL_TEXTURE_2D, m_TextureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER));
	GLfloat borderColor[] = { 1.0, 1.0, 1.0, 1.0 };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_TextureID, 0);
}

void Texture::CreateHDRTexture(unsigned short colorAttachment)
{
	glGenTextures(1, &m_TextureID);
	glBindTexture(GL_TEXTURE_2D, m_TextureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, SCREEN_WIDTH, SCREEN_HEIGHT, 0, GL_RGBA, GL_FLOAT, NULL);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + colorAttachment, GL_TEXTURE_2D, m_TextureID, 0);
}

void Texture::CreateTextureForFrameBuffer()
{
	glGenTextures(1, &m_TextureID);
	glBindTexture(GL_TEXTURE_2D, m_TextureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, SCREEN_WIDTH, SCREEN_HEIGHT, 0, GL_RGBA, m_dataType, NULL);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + m_colorAttachment, GL_TEXTURE_2D, m_TextureID, 0);
}
