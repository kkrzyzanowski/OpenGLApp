#pragma once
#include "..\glm\glm.hpp"
#include "..\glm\gtc\matrix_transform.hpp"
#include "..\glm\gtc\type_ptr.hpp"
#include "..\Rendering\Renderer.h"
class RayDrawer
{
public:
	RayDrawer();
	void DrawRay(glm::vec3 RayOrigin, glm::vec3 rayDirection, float distance, Renderer* renderer);
	~RayDrawer();
};

