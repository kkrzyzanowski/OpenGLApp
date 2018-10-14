#pragma once
#define _USE_MATH_DEFINES
#include <GL\glew.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "Texture.h"
#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtc\type_ptr.hpp"

enum CamView
{
	STATIC = 0, DYNAMIC = 1
};
class Shape
{
public:
	Shape(CamView camView = CamView::DYNAMIC);
	virtual void CreateShape(const GLfloat* points, unsigned int* orderIndex) = 0 {};
	VertexArray* GetVertexArray();
	VertexBuffer* GetVertexBuffer();
	IndexBuffer* GetIndexBuffer();
	ShaderManager GetShaderManager();
	Texture* GetTexture();
	virtual void TurnOffShapeElements() {};
	virtual void Update() = 0 {};
	void InitializeShapeView(glm::mat4& view);
	virtual void GenerateShaders() =  0 {};
	void SetOutsideLight(glm::vec3& light);
	glm::vec3 Shape::GetLight();
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
	glm::mat4 mvp;
	glm::mat4 model;
	glm::mat4 view;
	glm::mat4 proj;
	glm::vec3 outsideLight;
	glm::vec3 insideLightPos;
	CamView state;
};

