#pragma once
#include<GL\glew.h>
#include<GLFW\glfw3.h>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include "glm\gtc\matrix_transform.hpp"
enum ShaderType
{
	NONE = -1, VERTEX, FRAGMENT
};
class Shader
{
private:
	unsigned int m_ShaderID;
	std::string m_ShaderSource;
	std::string m_filePath;
	ShaderType m_ShaderType;
	std::unordered_map<std::string, int> m_uniformLocationCache;
public:
	Shader(const std::string & filepath);

	void Bind() const;
	void UnBind() const;

	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3, unsigned int program);
	void SetUniform2f(const std::string & name, float v0, float v1, unsigned int program);
	void SetUniformMat4f(const std::string& name, const glm::mat4& mat, unsigned int program);
	void SetUniform1i(const std::string& name, int value, unsigned int program);
	std::string ParseShader(const std::string & source);
	unsigned int CompileShader(const std::string & source, unsigned int type);
	inline unsigned int GetShaderID()
	{
		return m_ShaderID;
	}
	 ~Shader();

private:
	void CreateShader(const std::string& tShader);
	int GetUniformLocation(const std::string & name, unsigned int programShader);
};

