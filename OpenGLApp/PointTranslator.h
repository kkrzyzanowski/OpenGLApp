#pragma once
#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtc\type_ptr.hpp"
class PointTranslator
{
public:
	glm::vec2 MousePointPx;
	glm::vec2 ScaledMousePoint;

	glm::mat4 proj;
	glm::mat4 view;

	glm::vec3 perspectivePointPos;
	glm::vec4 viewPort;
	PointTranslator();
	void SetMousePoint(double x, double y);
	void CalculateScaledMousePoint();
	glm::vec3 GetPerspectivePoint(float zModel);
	
	
};

