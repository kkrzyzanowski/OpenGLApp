#pragma once
#include <vector>
#include <string>
#include "Texture.h"

namespace AppEngine
{
	class CubeMapTexture :
		public Texture
	{
	public:
		CubeMapTexture(std::vector<std::string> faces);
		void Bind() const override;
		void UnBind() const override;
		~CubeMapTexture();
	};
}
