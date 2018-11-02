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
#include "MaterialType.h"
enum CamView
{
	STATIC = 0, DYNAMIC = 1
};
enum SourceShapeType
{
	DIFFUSE = 0,
	LIGHT = 1,
	PARTICLE = 2,
};
class Shape
{
public:
	Shape();
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
	void SetEyeCamPos(glm::vec3& pos);
	void SetSourceShapeType(SourceShapeType shaderType);
	void SetShape();
	glm::vec3 Shape::GetInsideLight();
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
	void CreateType();
	glm::mat4 mvp;
	glm::mat4 model;
	glm::mat4 view;
	glm::mat4 proj;
	
	glm::vec3 insideLightPos;
	glm::vec3 camEyePos;


	CamView state;
	SourceShapeType sourceShapeType;
	ShapeType* type;
	Shape* light;
	glm::vec3 outsideLight;
};

