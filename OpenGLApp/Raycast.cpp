#include <iostream>
#include "Raycast.h"
#include "Config.h"

Raycast::Raycast(double xPos, double yPos, unsigned int distance, glm::mat4 projection, glm::mat4 view)
{
	this->proj = projection;
	this->view = view;
	rayDistance = distance;
	x = (xPos * 2.0f) / SCREEN_WIDTH  - 1.0f;
	y = 1.0f - (yPos * 2.0f) / SCREEN_HEIGHT;
	z = 1.0f;
	ray_nds = glm::vec3(x, y, 1.0f);
	rayStartClip = glm::vec4(x, y, -1.0f, 1.0f);
	rayEndClip = glm::vec4(x, y, 0.0f, 1.0f);
	CalculateMouseRay();
}

void Raycast::InverseToEyeCoords()
{
	rayStartCamera = glm::inverse(proj) * rayStartClip;
	rayStartCamera /= rayStartCamera.w;
	rayStartWorld = glm::inverse(view) * rayStartCamera;
	rayStartWorld /= rayStartWorld.w;
	rayEndCamera = glm::inverse(proj) * rayEndClip;
	rayEndCamera /= rayEndCamera.w;
	rayEndWorld = glm::inverse(view) * rayEndCamera;
	rayEndWorld /= rayEndWorld.w;
	//startRay = glm::vec4(startRay.x, startRay.y, -1.0f, 0.0f);
}

void Raycast::InverseToWorldCoords()
{
	/*glm::vec4 worldCoords = glm::inverse(view) * startRay;
	worldRay = glm::vec3(-worldCoords.x, -worldCoords.y, worldCoords.z);*/
	rayDirWorld = (rayEndWorld - rayStartWorld);
	origin = glm::vec3(rayStartWorld);
	worldRayNormalized = glm::normalize(glm::vec3(rayDirWorld.x, rayDirWorld.y, rayDirWorld.z));
	std::cout << "Ray Direciton: " << worldRayNormalized.x << " y: " <<
		worldRayNormalized.y << " z: " << worldRayNormalized.z << std::endl;
	
}

void Raycast::CalculateMouseRay()
{
	InverseToEyeCoords();
	InverseToWorldCoords();
}

bool Raycast::IntersectionInRange(float start, float end)
{
	glm::vec3 startPoint = GetPointFromRay(worldRayNormalized, start);
	glm::vec3 endPoint = GetPointFromRay(worldRayNormalized, end);
	return false;
}

glm::vec3 Raycast::GetPointFromRay(glm::vec3 ray, float distance)
{
	return glm::vec3();
}

glm::vec3 Raycast::GetWorldRayDirection()
{
	return worldRayNormalized;
}

glm::vec3 Raycast::GetRayOrigin()
{
	return origin;
}


Raycast::~Raycast()
{
}
