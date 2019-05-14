#pragma once
#include "Texture.h"
class CubeMapTexture :
	public Texture
{
public:
	CubeMapTexture(std::vector<std::string> faces);
	void Bind() const override;
	void UnBind() const override;
	~CubeMapTexture();
};

