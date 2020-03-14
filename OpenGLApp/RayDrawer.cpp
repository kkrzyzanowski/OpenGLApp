#include "RayDrawer.h"


RayDrawer::RayDrawer()
{
}

void RayDrawer::DrawRay(glm::vec3 RayOrigin, glm::vec3 rayDirection, float distance, Renderer* renderer)
{
	glm::vec3 endPoint = RayOrigin + glm::vec3(0.0f, 0.0f, rayDirection.z * distance);
	renderer->DrawLine(RayOrigin, endPoint);
}


RayDrawer::~RayDrawer()
{
}
