#include "Texture.h"
#include "Config.h"

Texture::Texture(const std::string& path, unsigned int slot, int mode) : m_path(path), m_slot(slot), m_TextureID(0), m_localBuffer(nullptr),
m_width(0), m_height(0), m_BPP(0)
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

Texture::Texture(): m_path(""), m_slot(0), m_TextureID(0), m_localBuffer(nullptr),
m_width(0), m_height(0), m_BPP(0)
{

}


Texture::~Texture()
{
	GLCall(glDeleteTextures(1, &m_TextureID));
}

void Texture::Bind() const
{
	GLCall(glActiveTexture(GL_TEXTURE0 + m_slot));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_TextureID));
}

void Texture::UnBind() const
{
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}

void Texture::CreateFrameBufferTexture()
{
	glGenTextures(1, &m_TextureID);
	glBindTexture(GL_TEXTURE_2D, m_TextureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1280, 720, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, m_TextureID, 0);

	GLenum DrawBuffers[1] = { GL_COLOR_ATTACHMENT0 };
	glDrawBuffers(1, DrawBuffers); // "1" is the size of DrawBuffers
}
