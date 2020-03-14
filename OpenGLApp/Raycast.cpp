#include <iostream>
#include "Raycast.h"
#include "Config.h"

Raycast::Raycast(double xPos, double yPos, unsigned int distance, glm::mat4 projection, glm::mat4 view)
{
	this->proj = projection;
	this->view = view;
	rayDistance = distance;
	x = ((xPos * 2.0f) / SCREEN_WIDTH ) - 1.0f;
	y = 1.0f - ((yPos * 2.0f) / SCREEN_HEIGHT);
	ray_nds = glm::vec3(x, y, 1.0f);
	ray_clip = glm::vec4(x, y, -1.0, 1.0f);
}

void Raycast::InverseToEyeCoords()
{
	rayEye = glm::inverse(proj) * ray_clip;
	rayEye = glm::vec4(rayEye.x, rayEye.y, -1.0f, 0.0f);
	//startRay = glm::vec4(startRay.x, startRay.y, -1.0f, 0.0f);
}

void Raycast::InverseToWorldCoords()
{
	/*glm::vec4 worldCoords = glm::inverse(view) * startRay;
	worldRay = glm::vec3(-worldCoords.x, -worldCoords.y, worldCoords.z);*/
	rayWorld = glm::inverse(view) * rayEye;
	worldRay = glm::normalize(rayWorld);
	std::cout << "MOuse pos normalized equals x: " << worldRay.x << " y: " <<
		worldRay.y << " z: " << worldRay.z << std::endl;
	
}

void Raycast::CalculateMouseRay()
{
	InverseToEyeCoords();
	InverseToWorldCoords();
}

bool Raycast::IntersectionInRange(float start, float end)
{
	glm::vec3 startPoint = GetPointFromRay(worldRay, start);
	glm::vec3 endPoint = GetPointFromRay(worldRay, end);
	return false;
}

glm::vec3 Raycast::GetPointFromRay(glm::vec3 ray, float distance)
{
	return glm::vec3();
}

glm::vec3 Raycast::GetWorldRay()
{
	return worldRay;
}


Raycast::~Raycast()
{
}
