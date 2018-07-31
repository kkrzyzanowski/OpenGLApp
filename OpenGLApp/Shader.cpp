#include "Shader.h"
#include "Renderer.h"


Shader::Shader(const std::string & filepath) : m_filePath(filepath), m_ShaderType(ShaderType::NONE)
{
	m_ShaderSource = ParseShader(m_filePath);
	CreateShader(m_ShaderSource);
}

void Shader::Bind() const
{
}

void Shader::UnBind() const
{
}


  void Shader::CreateShader(const std::string & ShaderSource)
{	
	if (m_ShaderType == ShaderType::VERTEX)
		m_ShaderID = CompileShader(ShaderSource, GL_VERTEX_SHADER);
	else if (m_ShaderType == ShaderType::FRAGMENT)
		m_ShaderID = CompileShader(ShaderSource, GL_FRAGMENT_SHADER);
}

  void Shader::SetUniform4f(const std::string & name, float v0, float v1, float v2, float v3)
  {
  }

  std::string Shader::ParseShader(const std::string & source)
{
	std::ifstream stream(source);
	size_t dotPos = source.find('.');
	std::string extension = source.substr(dotPos+1, source.length());

	if(std::strcmp(extension.c_str() , "frag") == 0)
	{
		m_ShaderType = ShaderType::FRAGMENT;
	}
	else if (std::strcmp(extension.c_str(), "vert")== 0)
	{
		m_ShaderType = ShaderType::VERTEX;
	}
	 std::string line;
	 std::stringstream ss;
	 while (getline(stream, line))
	 {
		 ss << line << '\n';
	 }
	 return ss.str();
 }

unsigned int Shader::CompileShader(const std::string & source, unsigned int type)
{
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str(); 
	GLCall(glShaderSource(id, 1, &src, nullptr));
	GLCall(glCompileShader(id));

	int result;
	GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
	if (result == GL_FALSE)
	{
		int length;
		GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
		char* message = (char*)alloca(sizeof(char) * length);
		GLCall(glGetShaderInfoLog(id, length, &length, message));
		GLCall(glDeleteShader(id));
		return -1;
	}

	return id;
}


Shader::~Shader()
{
}


