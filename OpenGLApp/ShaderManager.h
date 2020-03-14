#include "Shader.h"
#include <vector>
#include <unordered_map>
#pragma once
class ShaderManager
{
public:
	ShaderManager();
	~ShaderManager();
	void AddShadersToProgram(std::vector<Shader*> shader);
	void CreateProgram(const char* name);
	unsigned int GetProgram(const char* name);
	unsigned int GetProgram();
	void SetUniform4f(unsigned int location, float v0, float v1, float v2, float v3);
	void Bind();
	void UnBind();
	void ActivateProgram(const char* programName);
private:
	std::unordered_map<const char*, unsigned int> m_Program;
	const char* activeProgram;
};

