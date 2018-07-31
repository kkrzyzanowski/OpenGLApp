#include "Shape.h"
#include "Renderer.h"

Shape::Shape(Shapes shape)
{
	GLfloat g_vertex_buffer_data[] = {
	 -1.0f,
	 -1.0f, //0
	 0.0f,
	 0.0f, //1
	 -1.0f,
	 0.0f, //2
	 0.0f,
	 -1.0f };//3
	 unsigned int indexes[] = { 0,
	 3,
	 1,
	 1,
	 2,
	 0 };


	CreateShape(g_vertex_buffer_data, indexes);
}

void Shape::CreateShape(const GLfloat* points, unsigned int* orderIndex)
{
	

	va = new VertexArray();
	 vb = new VertexBuffer(points, sizeof(float) * 4 * 2);

	 layout = new VertexBufferLayout();
	layout->Push<float>(2);
	va->AddBuffer(*vb, *layout);
	 ib = new IndexBuffer(orderIndex, 6);
}

VertexArray*  Shape::GetVertexArray()
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
Shape::~Shape()
{
	GLCall(glDisableVertexAttribArray(0));
}
