#pragma once
#include<GL\glew.h>
#include<GLFW\glfw3.h>
#include <fstream>
#include <sstream>
#include <string>
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
public:
	Shader(const std::string & filepath);

	void Bind() const;
	void UnBind() const;

	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
	std::string ParseShader(const std::string & source);
	unsigned int CompileShader(const std::string & source, unsigned int type);
	inline unsigned int GetShaderID()
	{
		return m_ShaderID;
	}
	 ~Shader();

private:
	void CreateShader(const std::string& tShader);
	unsigned int GetUniformLocation(const std::string & name);
};

