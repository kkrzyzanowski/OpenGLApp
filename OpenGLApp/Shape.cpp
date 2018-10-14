#include "Shape.h"
#include "Renderer.h"


Shape::Shape(CamView camView)
{
	state = camView;
}

VertexArray* Shape::GetVertexArray()
{
	return va;
}

VertexBuffer* Shape::GetVertexBuffer()
{
	return vb;
}

IndexBuffer* Shape::GetIndexBuffer()
{
	return ib;
}
ShaderManager Shape::GetShaderManager()
{
	return sm;
}
Texture * Shape::GetTexture()
{
	return texture;
}
void Shape::InitializeShapeView(glm::mat4& view)
{
	this->view = view;
}
void Shape::SetOutsideLight(glm::vec3& light)
{
	outsideLight = light;
}
glm::vec3 Shape::GetLight()
{
	return insideLightPos;
}
Shape::~Shape()
{
	GLCall(glDisableVertexAttribArray(0));
}


