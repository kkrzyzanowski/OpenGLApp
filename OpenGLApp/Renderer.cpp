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

void Renderer::Draw(int count, GLenum mode) const
{
	GLCall(glDrawElements(mode, count, GL_UNSIGNED_INT, nullptr));
}

void Renderer::DrawLine(glm::vec3 start, glm::vec3 end)
{
	glBegin(GL_LINES);
		glVertex3f(start.x, start.y, start.z);
		glVertex3f(end.x, end.y, end.z);
	glEnd();
}

void Renderer::Clear() const
{
	GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}
