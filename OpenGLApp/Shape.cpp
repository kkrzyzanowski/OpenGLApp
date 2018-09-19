#include "Shape.h"
#include "Renderer.h"

Shape::Shape(Shapes shape)
{
	GLfloat g_vertex_buffer_data[] = {
	 -1.0f, -1.0f, 0.5f, 0.0f, 0.0f,//0
	 0.0f, 0.0f, 0.5f, 1.0f, 0.0f, //1
	 -1.0f,  0.0f, 0.5f, 1.0f, 1.0f, //2
	 0.0f, -1.0f, 0.5f, 0.0f, 1.0f, //3
	 -1.0f, -1.0f, -0.5f, 0.0f, 0.0f,// 4
	 0.0f, 0.0f, -0.5f, 1.0f, 0.0f, // 5
	 -1.0f,  0.0f, -0.5f, 1.0f, 1.0f, // 6
	 0.0f, -1.0f, -0.5f, 0.0f, 1.0f };// 7
	 unsigned int indexes[] = { 0, 3, 1,
	 1, 2, 0,
	 0, 4, 2,
	 2, 4, 6, 
	 6, 4, 5,
	 5, 4, 7,
	 7, 5, 1,
	 1, 3, 7};


	CreateShape(g_vertex_buffer_data, indexes);
}

void Shape::CreateShape(const GLfloat* points, unsigned int* orderIndex)
{
	GLCall(glEnable(GL_BLEND));
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

	va = new VertexArray();
	 vb = new VertexBuffer(points, sizeof(float) * 8 * 3 * 2);

	 layout = new VertexBufferLayout();
	layout->Push<float>(3); // vertexes
	layout->Push<float>(2); //textcoorssd
	va->AddBuffer(*vb, *layout);
	 ib = new IndexBuffer(orderIndex, 24);
	 texture = new Texture("Images\\BrickMedievalBlocks0129_2_M.jpg");
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
Texture * Shape::GetTexture()
{
	return texture;
}
Shape::~Shape()
{
	GLCall(glDisableVertexAttribArray(0));
}
