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

void Renderer::Draw(VertexArray& va, IndexBuffer& ib, ShaderManager& sm) const
{
	sm.Bind();
	ib.Bind();
	va.Bind();
	GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::Clear() const
{
	GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT));
}
