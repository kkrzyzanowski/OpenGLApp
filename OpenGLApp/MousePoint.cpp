#include "MousePoint.h"
#include "Config.h"

MousePoint::MousePoint()
{
}

void MousePoint::SetMousePoint(double x, double y)
{
	MousePointPx.x = x;
	MousePointPx.y = y;
}

void MousePoint::CalculateScaledMousePoint()
{
	ScaledMousePoint.x = (MousePointPx.x * 2.0f) / SCREEN_WIDTH - 1.0f;
	ScaledMousePoint.y = 1.0f - (MousePointPx.y * 2.0f) / SCREEN_HEIGHT;
}

glm::vec3 MousePoint::GetPerspectivePoint()
{
	glm::vec4 startClip = glm::vec4(ScaledMousePoint, -1.0f, 1.0f);
	glm::vec4 startCamera = glm::inverse(proj) * startClip;
	startCamera /= startCamera.w;
	glm::vec4 resultPoint = glm::inverse(view) * startCamera;
	resultPoint /= resultPoint.w;
	return (glm::vec3)resultPoint;
}
