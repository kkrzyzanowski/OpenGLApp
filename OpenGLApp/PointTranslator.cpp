#include "PointTranslator.h"
#include "Config.h"

PointTranslator::PointTranslator()
{
	viewPort = glm::vec4(0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void PointTranslator::SetMousePoint(double x, double y)
{
	MousePointPx.x = x;
	MousePointPx.y = y;
}

void PointTranslator::CalculateScaledMousePoint()
{
	ScaledMousePoint.x = ((MousePointPx.x * 2.0f) / SCREEN_WIDTH) - 1.0f;
	ScaledMousePoint.y = 1.0f - (MousePointPx.y * 2.0f) / SCREEN_HEIGHT;
}

glm::vec3 PointTranslator::GetWorldPoint()
{
	
	//glm::vec3 mousePos(MousePointPx.x, MousePointPx.y, 1.0f);
	//glm::mat4 modelview = view * model;
	glm::vec4 startClip = glm::vec4(ScaledMousePoint, 0.0f, 1.0f);;
	glm::vec4 mouseEyeCoords = glm::inverse(proj) * startClip;
	mouseEyeCoords.z = -1.0f;
	glm::vec4 mouseWorldCoords = glm::inverse(view) * mouseEyeCoords;
	//inverseProj = glm::vec4(inverseProj.x, inverseProj.y, -1.0f, 0.0f);
	
	glm::vec3 pos = glm::vec3(
		mouseWorldCoords.x,
		mouseWorldCoords.y,
		mouseWorldCoords.z
	);
	
	//glm::vec3 resultPoint = glm::unProject(mousePos, modelview, proj, viewPort);
	//resultPoint.z = 0.0f;
	return pos;
}

//MousePoint MousePoint::operator-(MousePoint& mp)
//{
//	MousePoint point;
//	point = mp.GetPerspectivePoint() - this->GetPerspectivePoint();
//}
