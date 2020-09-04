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
#include "Physics.h"

static std::vector<long> shape_ids;
unsigned long GenerateId(RGB &rgb);

enum CamView
{
	STATIC = 0, DYNAMIC = 1, MOVABLE = 2
};
enum SourceShapeType
{
	DIFFUSE = 0,
	LIGHT = 1,
	PARTICLE = 2,
	PRIMITIVE = 3,
	NO_TYPE
};
enum ShapeState
{
	CREATING, EXISTING, NOT_EXISTING
};

enum Direction
{
	UP, DOWN, LEFT ,RIGHT, FORWARD, BACKWARD
};
class Shape
{
public:
	Shape();
	Shape(SourceShapeType sourceType);
	virtual void CreateShape(const GLfloat* points, unsigned int* orderIndex, unsigned int countVertices, unsigned int countIndexes = 0);
	virtual void CreateShapev2(const GLfloat*& points, unsigned int*& orderIndex, unsigned int countVertices, unsigned int countIndexes = 0);
	
	//vertex methods
	VertexArray* GetVertexArray();
	VertexBuffer* GetVertexBuffer();
	IndexBuffer* GetIndexBuffer();

	//shader methods
	ShaderManager GetShaderManager();

	//texture methods
	Texture* GetTexture(std::string name);
	Texture* GetTexture(unsigned int texId);
	virtual glm::vec3 GetNormal() = 0 {};
	virtual void TurnOffShapeElements();
	virtual void Update() = 0 {};
	virtual void InitializeShapeView(glm::mat4& view);
	virtual void GenerateShaders() =  0 {};
	 glm::vec3 GetShapeCenterPoint();
	void ApplyProjectionMatrix(glm::mat4 proj);
	void SetOutsideLight(glm::vec3& light);
	void SetEyeCamPos(glm::vec3& pos);
	SourceShapeType GetSourceShapeType();
	void SetShape();
	void RotateNormals(float rotation, glm::vec3 rotationAxis);
	virtual void Translate(Direction dir, float value);
	void Scale(float value);
	void Rotate(float value);
	glm::vec3 Shape::GetInsideLight();
	ShapeState GetCreationState();
	std::array<float, 3> GetPosition();
	void UpdatePickedShape();

	std::vector<glm::vec3> GetVertices(GLfloat* objectData, size_t elements);
	std::vector<std::array<glm::vec3, 3>> GetTriangles(std::vector<glm::vec3>& vertices, size_t* indices, int indices_count);
	std::vector<std::vector<std::array<glm::vec3, 3>>> GetFaces(std::vector<std::array<glm::vec3, 3>>& triangles);
	std::vector<std::array<glm::vec3, 2>> Shape::GetEdges(GLfloat* objectData);
	void TranslatePoints(glm::mat4& mvp, Vertices& verts);

	std::vector<std::array<glm::vec3, 3>> GetTriangles();
	unsigned long Id;

	ShapeParameters shapeParams;
	ShapeElements shapeElements;

	glm::mat4 GetModel() const { return mvp.model; };

	~Shape();
protected:
	virtual void CreateMVPMatrix() {};
	void CreateType();
	void GeneratePickedShaders();

	VertexArray* va;
	VertexBuffer*  vb;
	VertexBufferLayout* layout;
	IndexBuffer* ib;

	std::vector<std::string> paths;
	std::vector<Texture*> textures;

	std::vector<Shader*> shaders;
	std::vector<Shader*> pickedShaders;
	ShaderManager sm;

	std::vector<glm::vec3> normals;
	glm::mat4 mvpResult;
	MVP mvp;
	std::string ShapeName;
	glm::vec3 shapeCoords;

	glm::vec3 insideLightPos;
	glm::vec3 camEyePos;

	Physics physics;
	CamView camState;
	SourceShapeType sourceShapeType;
	ShapeStateType* type;
	ShapeState shapeState;
	
	Shape* light;
	glm::vec3 outsideLight;
	RGB rgbCheck;


};
