#include "ShaderManager.h"

void ShaderManager::AddShaderFunction(const ShaderFunction& func, const std::vector<ShaderParams>& params)
{
	shaderFunctions.emplace_back(func, params);
}

void ShaderManager::ExecuteShaderFunction(std::vector<Shader*> shaders, unsigned int program)
{
	for (auto& [func, param] : shaderFunctions)
	{
		func(shaders, program, param);
	}
}

void ShaderManager::AddShader(const char* path)
{
	shaders.push_back(new Shader(path));
}

void ShaderManager::AddShaders(std::vector<Shader*>& shaders)
{
	this->shaders.insert(this->shaders.end(), shaders.begin(), shaders.end());
}

void ShaderManager::AddShaders(const std::vector<const char*>& shaderPaths)
{
	for (auto path : shaderPaths)
	{
		shaders.push_back(new Shader(path));
	}
}

void ShaderManager::DeleteShader(short int index)
{
	shaders.erase(shaders.begin() + index);
}

Shader* ShaderManager::GetShader(short int index)
{
	return shaders[index];
}
