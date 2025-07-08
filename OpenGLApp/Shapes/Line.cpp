#include "Line.h"

unsigned int orderIndex[] = { 0, 1 };


Line::Line(ShapesBuilder& builder): Shape(builder)
{
	this->points = { glm::vec3(), glm::vec3() };
}

Line::Line(ShapesBuilder&& builder) : Shape(std::move(builder))
{
	this->points = { glm::vec3(), glm::vec3() };
}

void Line::Create(const GLfloat* points, unsigned int* orderIndex, unsigned int countVertices, unsigned int countIndexes, unsigned int dataSize)
{
	/*va = new VertexArray();
	vb = new VertexBuffer(points, sizeof(float) * countVertices * 3);
	layout = new VertexBufferLayout();
	layout->Push<float>(3);
	va->AddBuffer(*vb, *layout);
	ib = new IndexBuffer(orderIndex, countIndexes);*/
	bm->CreateBuffersOnlyVertex(points, orderIndex, countVertices, countIndexes);
}

glm::vec3 Line::GetNormal()
{
	return glm::vec3();
}

void Line::Update()
{
	sc.EnableUse();
	ShaderTypeGenerator::UpdateModel(shaders, sc.GetCurrentProgram(), mvp.model);
	bm->BindBuffers();
	sc.DisableUse();
}

void Line::Translate(const glm::vec3& valueToMove)
{
}

//void Line::Translate(Direction dir, float value)
//{
//	switch (dir)
//	{
//	case UP:
//		for (glm::vec3& point : points)
//		{
//			point += glm::vec3(0.0f, value, 0.0f);
//		}
//		break;
//	case DOWN:
//		for (glm::vec3& point : points)
//		{
//			point -= glm::vec3(0.0f, value, 0.0f);
//		}
//		break;
//	case LEFT:
//		for (glm::vec3& point : points)
//		{
//			point -= glm::vec3(value, 0.0f, 0.0f);
//		}
//		break;
//	case RIGHT:
//		for (glm::vec3& point : points)
//		{
//			point += glm::vec3(value, 0.0f, 0.0f);
//		}
//		break;
//	case FORWARD:
//		for (glm::vec3& point : points)
//		{
//			point += glm::vec3(0.0f, 0.0f, value);
//		}
//		break;
//	case BACKWARD:
//		for (glm::vec3& point : points)
//		{
//			point -= glm::vec3(0.0f, 0.0f, value);
//		}
//		break;
//	default:
//		break;
//	}
//}

void Line::SetPoints(std::vector<glm::vec3> points)
{
	this->points = points;
}


Line::~Line()
{
}

void Line::CreateMVPMatrix()
{
	mvp.model = glm::mat4(1.0f);
}
