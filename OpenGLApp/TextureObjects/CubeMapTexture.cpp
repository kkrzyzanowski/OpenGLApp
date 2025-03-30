#include "CubeMapTexture.h"
#include "../Rendering/Renderer.h"



CubeMapTexture::CubeMapTexture(std::vector<std::string> paths): Texture()
{
	GLCall(glGenTextures(1, &m_TextureID));
	GLCall(glBindTexture(GL_TEXTURE_CUBE_MAP, m_TextureID));

	for(int i =0; i<paths.size(); i++)
	{
		name = paths[i].substr(paths[i].find_last_of('/\\') + 1);
		name = paths[i].substr(0, paths[i].find_last_of('.'));
		m_localBuffer = stbi_load(paths[i].c_str(), &m_width, &m_height, &m_BPP, 4);
		if (m_localBuffer)
		{
			GLCall(glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_localBuffer));
			stbi_image_free(m_localBuffer);
		}
			
	}

		GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
		GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
		GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
		GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
		GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE));

		GLCall(glBindTexture(GL_TEXTURE_CUBE_MAP, 0));
}

void CubeMapTexture::Bind() const
{
	GLCall(glActiveTexture(GL_TEXTURE0));
	GLCall(glBindTexture(GL_TEXTURE_CUBE_MAP, m_TextureID));
}

void CubeMapTexture::UnBind() const
{
	GLCall(glBindTexture(GL_TEXTURE_CUBE_MAP, 0));
}


CubeMapTexture::~CubeMapTexture()
{
}
