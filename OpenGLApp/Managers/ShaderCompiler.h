#pragma once
#include <vector>
#include <unordered_map>
#include "..\Shaders\ShaderClasses\Shader.h"

class ShaderCompiler
{
public:
	ShaderCompiler();
	~ShaderCompiler();
	void AddShadersToProgram(std::vector<Shader*> shader);
	void AddShaderToProgram(Shader* shader);
	void CreateProgram(const char* name);
	unsigned int GetProgram(const char* name);
	unsigned int GetDefaultProgram();
	unsigned int GetCurrentProgram();
	inline unsigned int GetUniformBlockIndex() const { return uniformBlockIndex; }
	void SetUniform4f(unsigned int location, float v0, float v1, float v2, float v3);
	void EnableUse();
	void DisableUse();
	void ActivateDefaultProgram();
	void ActivateProgram(const char* name);
	void BindBlockData(const char* blockName);
private:
	void UniformBinder(unsigned int program);
	std::unordered_map<const char*, unsigned int> m_Program;
	const char* activeProgram;
	unsigned int uniformBlockIndex;
};

