#pragma once
#include <vector>
#include "..\Shaders\ShaderClasses\Shader.h"
#include "..\Managers\ShaderCompiler.h"
#include "..\Shaders\ShaderClasses\ShaderTypeGenerator.h"
#include "..\DataStructures.h"
#include "..\glm\glm.hpp"
#include "..\glm\gtc\matrix_transform.hpp"
#include "..\glm\gtc\type_ptr.hpp"

class StencilOutline
{
public:
	StencilOutline();
	void InitializeView(glm::mat4& camView);
	void InitializePerspective(glm::mat4& perspective);
	void InitializeModel(glm::mat4& model);
	void UpdateModel(glm::mat4& model);
	void UpdateView(glm::mat4& camView);
	void SetColor(glm::vec3 color = glm::vec3(1.0f, 0.0f, 0.0f));
	void BindMVMatrices();
	void UseShader();
	void Update();
	MVP mvpOutline;
	std::vector<Shader*> shaders;
	ShaderCompiler sc;
	glm::mat4 mvpResult;
	std::vector<ShaderParams> params;
private:
	glm::vec3 color;
};

