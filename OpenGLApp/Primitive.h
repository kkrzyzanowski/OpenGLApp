#pragma once
#include <vector>
#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtc\type_ptr.hpp"
class Primitive
{
public:
	Primitive();
	virtual void SetPoints(std::vector<glm::vec3> points) = 0 {};
	~Primitive();
};

