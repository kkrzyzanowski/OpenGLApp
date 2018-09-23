#include "ShaderManager.h"
#include "Renderer.h"


ShaderManager::ShaderManager(): m_Program(glCreateProgram())
{
}


ShaderManager::~ShaderManager()
{
}

unsigned int ShaderManager::AddShadersToProgram(std::vector<Shader*> Shaders)
{
	for each  (Shader* s in Shaders)
	{
		GLCall(glAttachShader(m_Program, s->GetShaderID()));
	}
	GLCall(glLinkProgram(m_Program));
	GLCall(glValidateProgram(m_Program));
	for each  (Shader* s in Shaders)
	{
		GLCall(glDeleteShader(s->GetShaderID()));
	}

	return m_Program;
}

unsigned int ShaderManager::GetProgram()
{
	return m_Program;
}


 void ShaderManager::SetUniform4f(unsigned int location,  float v0, float v1, float v2, float v3)
 {
	 GLCall(glUniform4f(location, v0, v1, v2, v3));
 }

 void ShaderManager::Bind()
 {
	 GLCall(glUseProgram(m_Program));
 }

 void ShaderManager::UnBind()
 {
	 GLCall(glUseProgram(0));
 }
