#pragma once
#include "..\Shapes\Shape.h"

class Cube: public Shape
{
public:
	Cube(ShapesBuilder& builder);
	Cube(ShapesBuilder&& builder);
	void Update() override;
	glm::vec3 GetNormal() override;
	~Cube();
private:
	
	/*template <typename Matrix, typename ... glm::mat4>
	void TransformateShape(Matrix arg, glm::mat4&... rest);*/
	void CreateMVPMatrix() override;
	void GenerateTextures(std::vector<Texture*>& textures) override;
};

