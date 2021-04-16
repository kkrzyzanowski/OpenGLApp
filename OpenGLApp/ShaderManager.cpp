#include "ShaderManager.h"
#include "Renderer.h"

#define PROGRAM_NAME "ShapeShader"

ShaderManager::ShaderManager() 
{
	m_Program.insert({ PROGRAM_NAME, glCreateProgram() });
	activeProgram = PROGRAM_NAME;
}


ShaderManager::~ShaderManager()
{
}

void ShaderManager::AddShadersToProgram(std::vector<Shader*> Shaders)
{
	for(Shader* s: Shaders)
	{
		GLCall(glAttachShader(m_Program.at(activeProgram), s->GetShaderID()));
	}
	GLCall(glLinkProgram(m_Program.at(activeProgram)));
	GLCall(glValidateProgram(m_Program.at(activeProgram)));
	for(Shader* s: Shaders)
	{
		GLCall(glDeleteShader(s->GetShaderID()));
	}
}

void ShaderManager::CreateProgram(const char* name)
{
	m_Program.insert({ name, glCreateProgram() });
}

unsigned int ShaderManager::GetProgram(const char* name)
{
	return m_Program.at(name);
}

unsigned int ShaderManager::GetProgram()
{
	return m_Program.at(PROGRAM_NAME);
}


 void ShaderManager::SetUniform4f(unsigned int location,  float v0, float v1, float v2, float v3)
 {
	 GLCall(glUniform4f(location, v0, v1, v2, v3));
 }

 void ShaderManager::Bind()
 {
	 GLCall(glUseProgram(m_Program.at(activeProgram)));
 }

 void ShaderManager::UnBind()
 {
	 GLCall(glUseProgram(0));
 }

 void ShaderManager::ActivateProgram(const char * programName)
 {
	 activeProgram = programName;
 }
