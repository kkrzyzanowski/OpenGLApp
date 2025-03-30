#include "ShaderCompiler.h"
#include "..\Rendering\Renderer.h"

#define PROGRAM_NAME "DefaultShaderProgram"

ShaderCompiler::ShaderCompiler() 
{
	m_Program.insert({ PROGRAM_NAME, glCreateProgram() });
	activeProgram = PROGRAM_NAME;
}


ShaderCompiler::~ShaderCompiler()
{
}

void ShaderCompiler::AddShadersToProgram(std::vector<Shader*> Shaders)
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

void ShaderCompiler::AddShaderToProgram(Shader* shader)
{
	
	GLCall(glAttachShader(m_Program.at(activeProgram), shader->GetShaderID()));
	GLCall(glLinkProgram(m_Program.at(activeProgram)));
	GLCall(glValidateProgram(m_Program.at(activeProgram)));
	GLCall(glDeleteShader(shader->GetShaderID()));
}

void ShaderCompiler::CreateProgram(const char* name)
{
	m_Program.insert({ name, glCreateProgram() });
}

unsigned int ShaderCompiler::GetProgram(const char* name)
{
	return m_Program.at(name);
}

unsigned int ShaderCompiler::GetCurrentProgram()
{
	return m_Program.at(activeProgram);
}

unsigned int ShaderCompiler::GetDefaultProgram()
{
	return m_Program.at(PROGRAM_NAME);
}


 void ShaderCompiler::SetUniform4f(unsigned int location,  float v0, float v1, float v2, float v3)
 {
	 GLCall(glUniform4f(location, v0, v1, v2, v3));
 }

 void ShaderCompiler::EnableUse()
 {
	 GLCall(glUseProgram(m_Program.at(activeProgram)));
 }

 void ShaderCompiler::DisableUse()
 {
	 GLCall(glUseProgram(0));
 }

 void ShaderCompiler::ActivateDefaultProgram()
 {
	 activeProgram = PROGRAM_NAME;
 }

 void ShaderCompiler::ActivateProgram(const char* name)
 {
	 activeProgram = name;
 }


 void ShaderCompiler::BindBlockData(const char* blockName)
 {
	 unsigned int currentProgram = GetCurrentProgram();
	 uniformBlockIndex = glGetUniformBlockIndex(currentProgram, blockName);
	 UniformBinder(currentProgram);
 }
 void ShaderCompiler::UniformBinder(unsigned int program)
 {
	 GLCall(glUniformBlockBinding(GetDefaultProgram(), uniformBlockIndex, 0));
 }
