#pragma once
#include "..\glm\glm.hpp"
#include "..\glm\gtc\matrix_transform.hpp"
#include "..\glm\gtc\type_ptr.hpp"
struct Physics
{
public:
	Physics();
	~Physics();
	float mass;
	glm::vec3 velocity;
	float acceleration;
	float drag;
	bool gravity;
	glm::vec3 gravityValue;

	Physics(float, glm::vec3, float, float, bool, glm::vec3);
};

