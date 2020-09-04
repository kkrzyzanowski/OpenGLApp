#pragma once
#include "glm/glm.hpp"
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

