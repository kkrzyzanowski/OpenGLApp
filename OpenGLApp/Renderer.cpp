#include "Renderer.h"



void GLClearError()
{
	while (glGetError() != GL_NO_ERROR);
}
bool GLLogCall(const char* function, const char* file, int line)
{
	while (GLenum error = glGetError())
	{
		std::cout << "Error : " << error << " " << function << " in file " << file << ", line " << line << std::endl;
		return false;
	}
	return true;
}