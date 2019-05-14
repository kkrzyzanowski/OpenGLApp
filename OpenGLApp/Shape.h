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
#include "ShaderTypeGenerator.h"
#include "MaterialType.h"
#include "DataStructures.h"


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
enum ShapeState
{
	CREATING, EXISTING, NOT_EXISTING
};

class Shape
{
public:
	Shape();
	virtual void CreateShape(const GLfloat* points, unsigned int* orderIndex, unsigned int countVertices, unsigned int countIndexes);
	VertexArray* GetVertexArray();
	VertexBuffer* GetVertexBuffer();
	IndexBuffer* GetIndexBuffer();
	ShaderManager GetShaderManager();
	Texture* GetTexture(std::string name);
	Texture* GetTexture(unsigned int texId);
	virtual void TurnOffShapeElements();
	virtual void Update() = 0 {};
	virtual void InitializeShapeView(glm::mat4& view);
	virtual void GenerateShaders() =  0 {};
	void SetOutsideLight(glm::vec3& light);
	void SetEyeCamPos(glm::vec3& pos);
	void SetSourceShapeType(SourceShapeType shaderType);
	void SetShape();
	glm::vec3 Shape::GetInsideLight();
	ShapeState GetState();
	~Shape();
protected:
	VertexArray* va;
	VertexBuffer*  vb;
	VertexBufferLayout* layout;
	IndexBuffer* ib;

	std::vector<std::string> paths;
	std::vector<Texture*> textures;

	std::vector<Shader*> shaders;
	ShaderManager sm;
	virtual void CreateMVPMatrix() {};
	void CreateType();
	glm::mat4 mvpResult;
	MVP mvp;
	std::string ShapeName;

	glm::vec3 insideLightPos;
	glm::vec3 camEyePos;


	CamView camState;
	SourceShapeType sourceShapeType;
	ShapeType* type;
	ShapeState shapeState;
	Shape* light;
	glm::vec3 outsideLight;
};

