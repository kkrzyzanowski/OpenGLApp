#pragma once
#include "../Shape.h"
#include "../ShapesBuilder.h"
class Sphere :
	public Shape
{
public:
	Sphere();
	Sphere(const ShapesBuilder builder);
	void Update() override;
	void GenerateShaders() override;
	glm::vec3 GetNormal() override;
	float GetRadius();
	~Sphere();
private:
	void CreateMVPMatrix() override;
	glm::vec3 normalLight;
	float radius;
	/*GLfloat* vertices;
	unsigned int* sphere_ix;*/
};

