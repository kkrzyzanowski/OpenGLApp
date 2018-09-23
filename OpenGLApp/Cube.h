#pragma once
#include "Shape.h"
class Cube: public Shape
{
public:
	Cube();
	void CreateShape(const GLfloat* points, unsigned int* oredrIndex) override;
	void TurnOffShapeElements() override;
	void Update(glm::mat4 camView) override;
	~Cube();
private:
	
	/*template <typename Matrix, typename ... glm::mat4>
	void TransformateShape(Matrix arg, glm::mat4&... rest);*/
	glm::mat4 mvp;
	glm::mat4 model;
	glm::mat4 view;
	glm::mat4 proj;
	void CreateMVPMatrix() override;
	void GenerateShaders() override;
};

