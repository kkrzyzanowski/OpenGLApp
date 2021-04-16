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
	ScaledMousePoint.x = (MousePointPx.x * 2.0f) / SCREEN_WIDTH - 1.0f;
	ScaledMousePoint.y = 1.0f - (MousePointPx.y * 2.0f) / SCREEN_HEIGHT;
}

glm::vec3 PointTranslator::GetPerspectivePoint(float zModel)
{
	
	//glm::vec3 mousePos(MousePointPx.x, MousePointPx.y, 1.0f);
	//glm::mat4 modelview = view * model;
	//float zValue = ((zModel * 2.0f) / 999.99f) - 1.0f;
	glm::vec4 startClip = glm::vec4(ScaledMousePoint, zModel, 1.0f);
	glm::vec4 inverseProj = glm::inverse(proj) * startClip;
	//inverseProj = glm::vec4(inverseProj.x, inverseProj.y, -1.0f, 0.0f);
	inverseProj /= inverseProj.w;
	glm::vec4 inverseView = glm::inverse(view) * inverseProj;
	glm::vec3 resultPoint = glm::vec3(inverseView / inverseView.w);
	//glm::vec3 resultPoint = glm::unProject(mousePos, modelview, proj, viewPort);
	//resultPoint.z = 0.0f;
	return resultPoint;
}

//MousePoint MousePoint::operator-(MousePoint& mp)
//{
//	MousePoint point;
//	point = mp.GetPerspectivePoint() - this->GetPerspectivePoint();
//}
