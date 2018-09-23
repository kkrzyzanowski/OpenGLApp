#include "Shader.h"
#include <vector>
#include <unordered_map>
#pragma once
class ShaderManager
{
public:
	ShaderManager();
	~ShaderManager();
	unsigned int AddShadersToProgram(std::vector<Shader*> shader);
	unsigned int GetProgram();
	void SetUniform4f(unsigned int location, float v0, float v1, float v2, float v3);
	void Bind();
	void UnBind();
private:
	unsigned int m_Program;
};

