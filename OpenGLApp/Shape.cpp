#include <algorithm>
#include <time.h>
#include <string>
#include "Shape.h"
#include "Renderer.h"
#include "glm/gtx/rotate_vector.hpp"

static bool RandomInitializer = false;
Shape::Shape()
{
	shapeState = ShapeState::CREATING;
	sourceShapeType = SourceShapeType::NO_TYPE;
	do
	{
		this->Id = GenerateId(this->rgbCheck);
	} while (std::find(shape_ids.begin(), shape_ids.end(), this->Id) != shape_ids.end());
	sm.ActivateProgram("ShapeShader");
	
}

Shape::Shape(SourceShapeType sourceType)
{
	shapeState = ShapeState::CREATING;
	sourceShapeType = sourceType;
}

void Shape::CreateShape(const GLfloat * points, unsigned int * orderIndex, unsigned int countVertices, unsigned int countIndexes)
{
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
glm::vec3 Shape::GetShapeCenterPoint()
{
	return shapeCoords;
}
void Shape::ApplyProjectionMatrix(glm::mat4 proj)
{
	this->mvp.proj = proj;
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
SourceShapeType Shape::GetSourceShapeType()
{
	return sourceShapeType;
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
void Shape::RotateNormals(float rotation)
{
	for(glm::vec3& normal : normals)
	{
		normal = glm::rotate(normal, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));
		std::cout << "Normal x: " << normal.x << " Normal y: " << normal.y << " Normal z: "
			<< normal.z << std::endl;
	}
}
void Shape::Translate(Direction dir, float value)
{
	switch (dir)
	{
	case UP:
		mvp.model = glm::translate(mvp.model, glm::vec3(0.0f, value, 0.0f));
		break;
	case DOWN:
		mvp.model = glm::translate(mvp.model, glm::vec3(0.0f, -value, 0.0f));
		break;
	case LEFT:
		mvp.model = glm::translate(mvp.model, glm::vec3(-value , 0.0f, 0.0f));
		break;
	case RIGHT:
		mvp.model = glm::translate(mvp.model, glm::vec3(value, 0.0f, 0.0f));
		break;
	case FORWARD:
		mvp.model = glm::translate(mvp.model, glm::vec3(0.0f, 0.0f, value));
		break;
	case BACKWARD:
		mvp.model = glm::translate(mvp.model, glm::vec3(0.0f, 0.0f, -value));
		break;
	default:
		break;
	}
}
void Shape::Scale(float value)
{
}
void Shape::Rotate(float value)
{
}
glm::vec3 Shape::GetInsideLight()
{
	return insideLightPos;
}
ShapeState Shape::GetState()
{
	return shapeState;
}
void Shape::UpdatePickedShape()
{
	sm.ActivateProgram("picked");
	sm.Bind();
	pickedShaders[0]->SetUniformMat4f("mvpResult", mvpResult, sm.GetProgram("picked"));
	sm.UnBind();
	sm.Bind();
	sm.ActivateProgram("ShapeShader");
	
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
void Shape::GeneratePickedShaders()
{
	pickedShaders.push_back(new Shader("Shaders\\PickingVertexShader.vert"));
	pickedShaders.push_back(new Shader("Shaders\\PickingFragmentShader.frag"));
	sm.CreateProgram("picked");
	sm.ActivateProgram("picked");
	sm.AddShadersToProgram(pickedShaders);
	sm.Bind();
	ShaderTypeGenerator::PickedShaderGenerator(pickedShaders, glm::vec3(rgbCheck.r/255.0f, rgbCheck.g/255.0f, rgbCheck.b/255.0f), mvpResult, sm.GetProgram("picked"));
	sm.UnBind();
	sm.ActivateProgram("ShapeShader");
}
unsigned long GenerateId(RGB &rgb)
{
	const int size = 8;
	const int idSize = 24;

if(!RandomInitializer)
{ 
	srand(time(NULL));
	RandomInitializer = true;
}

	rgb.r = rand() % 255;
	rgb.g = rand() % 255;
	rgb.b = rand() % 255;

	std::string id = std::to_string(rgb.r) + std::to_string(rgb.g) + std::to_string(rgb.b);

	return std::stol(id);
	
}


