#pragma once
#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtc\type_ptr.hpp"
#include "DataStructures.h"
class MVPManager
{
public:
	void ApplyProjectionMatrix(const glm::mat4 proj);
	void SetEyeCamPos(const glm::vec3& pos);
	virtual void ApplyShapeView(const glm::mat4& view);
	void UpdateModel(const glm::mat4& model);


	glm::vec3 camEyePos;
	MVP mvp;
};

