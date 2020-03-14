#pragma once
#include "Shape.h"
#include "ShapesBuilder.h"
class Cube: public Shape
{
public:
	Cube(const ShapesBuilder builder);
	void Update() override;
	glm::vec3 GetNormal() override;
	~Cube();
private:
	
	/*template <typename Matrix, typename ... glm::mat4>
	void TransformateShape(Matrix arg, glm::mat4&... rest);*/
	void CreateMVPMatrix() override;
	void GenerateShaders() override;
};

