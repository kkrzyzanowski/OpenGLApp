#pragma once
#include <vector>
#include "Shader.h"
#include "ShaderTypeGenerator.h"
#include "../../DataStructures.h"

class ShaderManager
{
public:

	void AddShaderFunction(const ShaderFunction& func, const std::vector<ShaderParams>& param);
	void ExecuteShaderFunction(std::vector<Shader*> shaders, unsigned int program);
	void AddShader(const char* path);
	void AddShaders(std::vector<Shader*>& shaders);
	void AddShaders(const std::vector<const char*>& shaderPaths);
	void DeleteShader(short int index);
	Shader* GetShader(short int index);
	void UpdateShaderParam(std::string& name, ShaderParams value);
	std::vector<Shader*> shaders;
	std::vector<Shader*> defferedShaders;
	std::vector<Shader*> pickedShaders;
	std::vector<std::pair<ShaderFunction, std::vector<ShaderParams>>> shaderFunctions;
	std::unordered_map<std::string, ShaderParams> params;
	
};

