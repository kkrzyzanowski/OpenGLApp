#pragma once
#include "..\Shapes\Shape.h"
class Sphere :
	public Shape
{
public:
	Sphere();
	Sphere(ShapesBuilder& builder);
	Sphere(ShapesBuilder&& builder);
	void Update() override;
	glm::vec3 GetNormal() override;
	float GetRadius() const;
	~Sphere();
private:
	void CreateMVPMatrix() override;
	glm::vec3 normalLight;
	float radius;
	/*GLfloat* vertices;
	unsigned int* sphere_ix;*/
};

