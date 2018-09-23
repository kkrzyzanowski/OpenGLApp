#pragma once
#include <GL\glew.h>
#include <GLFW/glfw3.h>
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "Texture.h"
#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtc\type_ptr.hpp"

 enum Shapes
{
	TRIANGLE = 9, RECTANGLE = 12, CUBE = 36
};
class Shape
{
public:
	Shape(Shapes shape);
	virtual void CreateShape(const GLfloat* points, unsigned int* orderIndex) = 0 {};
	VertexArray* GetVertexArray();
	VertexBuffer* GetVertexBuffer();
	IndexBuffer* GetIndexBuffer();
	ShaderManager GetShaderManager();
	Texture* GetTexture();
	virtual void TurnOffShapeElements() = 0 {};
	virtual void Update(glm::mat4 camView) = 0 {};
	~Shape();
protected:
	VertexArray* va;
	VertexBuffer*  vb;
	VertexBufferLayout* layout;
	IndexBuffer* ib;
	Texture* texture;
	std::vector<Shader*> shaders;
	ShaderManager sm;
	virtual void CreateMVPMatrix() {};
	virtual void GenerateShaders() {};
	glm::mat4 mvp;
	glm::mat4 model;
	glm::mat4 view;
	glm::mat4 proj;
};

