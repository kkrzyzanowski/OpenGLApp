#include "MVPManager.h"

void MVPManager::ApplyProjectionMatrix(const glm::mat4 proj)
{
	this->mvp.proj = proj;
}

void MVPManager::SetEyeCamPos(const glm::vec3& pos)
{
	camEyePos = pos;
}

void MVPManager::ApplyShapeView(const glm::mat4& view)
{
	this->mvp.view = view;
}

void MVPManager::UpdateModel(const glm::mat4& model)
{
	this->mvp.model = model;
}
