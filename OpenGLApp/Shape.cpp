#include "Shape.h"
#include "Renderer.h"
#include <algorithm>

Shape::Shape()
{
	shapeState = ShapeState::CREATING;
}

void Shape::CreateShape(const GLfloat * points, unsigned int * orderIndex, unsigned int countVertices, unsigned int countIndexes)
{
	GLCall(glEnable(GL_BLEND));
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
	
	va = new VertexArray();
	vb = new VertexBuffer(points, sizeof(float) * countVertices * (3 + 2 + 3));
	layout = new VertexBufferLayout();
	layout->Push<float>(3); // vertexes
	layout->Push<float>(2); //textcoorssd
	layout->Push<float>(3); // normals
	va->AddBuffer(*vb, *layout);
	ib = new IndexBuffer(orderIndex, countIndexes); //indexes count
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
Texture * Shape::GetTexture(std::string name)
{
	auto it = std::find_if(textures.begin(), textures.end(), [&name](Texture* tex) {return tex->GetTextureName() == name; });
	return *it;
}
void Shape::TurnOffShapeElements()
{
	va->UnBind();
	vb->UnBind();
	ib->UnBind();
	sm.UnBind();
}
void Shape::InitializeShapeView(glm::mat4& view)
{
	this->mvp.view = view;
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
ShapeState Shape::GetState()
{
	return shapeState;
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


