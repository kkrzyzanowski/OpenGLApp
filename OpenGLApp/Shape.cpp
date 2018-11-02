#include "Shape.h"
#include "Renderer.h"


Shape::Shape()
{
	
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
	if(sourceShapeType == SourceShapeType::DIFFUSE)
		outsideLight = light;
}
void Shape::SetEyeCamPos(glm::vec3 & pos)
{
	camEyePos = pos;
}
void Shape::SetSourceShapeType(SourceShapeType shapeType)
{
	sourceShapeType = shapeType;
}
void Shape::SetShape()
{
	switch (sourceShapeType)
	{
	case SourceShapeType::DIFFUSE:
	{
		type = new DiffuseShape();
		break;
	}
	case SourceShapeType::LIGHT:
	{
		type = new LightShape();
		break;
	}
	case SourceShapeType::PARTICLE:
	{
		type = new ParticleShape();
		break;
	}
	default:
	{
		type = new DiffuseShape();
		break;
	}
	}
}
glm::vec3 Shape::GetInsideLight()
{
	return insideLightPos;
}
Shape::~Shape()
{
	GLCall(glDisableVertexAttribArray(0));
}

void Shape::CreateType()
{
	switch (sourceShapeType)
	{
	case SourceShapeType::DIFFUSE:
	{
		type = new DiffuseShape();
		break;
	}
	case SourceShapeType::LIGHT:
	{
		type = new LightShape();
		break;
	}
	case SourceShapeType::PARTICLE:
	{
		type = new ParticleShape();
		break;
	}
	default:
		break;
	}
}


