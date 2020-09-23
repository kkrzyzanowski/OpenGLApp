#pragma once
#include "Shader.h"
#include "ShaderManager.h"
#include "ShaderTypeGenerator.h"
#include "DataStructures.h"
#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtc\type_ptr.hpp"
#include <vector>

class StencilOutline
{
public:
	StencilOutline();
	void InitializeView(glm::mat4& camView);
	void InitializePerspective(glm::mat4& perspective);
	void CalculateMvpResult();
	void UseShader();
	void Update();
	MVP mvpOutline;
	std::vector<Shader*> shaders;
	ShaderManager sm;
	glm::mat4 mvpResult;

private:
	void PreparingOutlineShader();
};

