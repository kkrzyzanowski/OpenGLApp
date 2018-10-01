#pragma once
#include "Shape.h"
class Sphere :
	public Shape
{
public:
	Sphere();
	void CreateShape(const GLfloat* points, unsigned int* orderIndex) override;
	void TurnOffShapeElements() override;
	void Update(glm::mat4 camView) override;
	~Sphere();
private:
	void CreateMVPMatrix() override;
	void GenerateShaders() override;
	/*GLfloat* vertices;
	unsigned int* sphere_ix;*/
};

