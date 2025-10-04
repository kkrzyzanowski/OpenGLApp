#pragma once
#include <cmath>
#include <functional>
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include "..\Shaders\ShaderClasses\ShaderTypeGenerator.h"
#include "..\MaterialType.h"
#include "..\DataStructures.h"
#include "..\Rendering\StencilOutline.h"
#include "..\Physics\Physics.h"
#include "..\Enums.h"
#include "..\Buffers\UniformBuffer.h"
#include "..\Managers\VertexManager.h"
#include "..\Managers\TextureManager.h"
#include "..\Managers\BufferManager.h"
#include "../Managers/ShaderCompiler.h"
#include "../Shaders/ShaderClasses/ShaderManager.h"
#include "../Config.h"
#include "..\Rendering\Renderer.h"
#include "VerticesCreator.h"
#include "..\glm\gtx\rotate_vector.hpp"

class ShapesBuilder;

static std::vector<long> shape_ids;
unsigned long GenerateId();

class Shape
{
public:
	Shape(ShapesBuilder& builder);
	Shape(ShapesBuilder&& builder);
	Shape(const Shape&) = default;
	virtual void Create(const GLfloat* points, unsigned int* orderIndex, unsigned int countVertices, unsigned int countIndexes, unsigned int* bufferDataSizes, unsigned int dataSize);
	void CreateInstancedShape(const GLfloat* points, unsigned int* orderIndex, unsigned int countVertices, unsigned int countIndexes);
	virtual void Create(const GLfloat* points, std::vector<int>& orderIndex, unsigned int countVertices, unsigned int countIndexes, unsigned int* bufferDataSizes, unsigned int dataSize);

	//shader methods
	const ShaderCompiler GetShaderCompiler() const;

	//texture methods
	Texture* GetTexture(std::string name);
	Texture* GetTexture(unsigned int texId);
	virtual void GenerateTextures(std::vector<Texture*>& textures);

	virtual glm::vec3 GetNormal() = 0;
	virtual void DeactivateShapeBufferParts();
	virtual void Update();
	virtual void AfterUpdate();

	virtual void ApplyShapeView(const glm::mat4& view);
	virtual void GenerateShaders();
	virtual void ApplyShaders();
	virtual void GenerateVertices();

	const glm::vec3 GetShapeCenterPoint() const;
	void ApplyProjectionMatrix(const glm::mat4 proj);
	void SetMainLight(const glm::vec3& light);
	void SetEyeCamPos(const glm::vec3& pos);
	const SourceShapeType GetSourceShapeType() const;
	void RotateNormals(float rotation, glm::vec3 rotationAxis);
	virtual void Translate(const glm::vec3& valueToMove);
	void SetPosition(const glm::vec3& pos);
	void Scale(float value);
	void Rotate(float value);
	void PassShaderParams(std::vector<ShaderParams> params);
	ShapeState GetCreationState() const;
	glm::vec3 GetPosition();

	ShapeType GetType();
	Shading GetShading() const;
	bool IsShadowTurnOn() const;
	bool IsHDROn() const;

	void InitializePickedShape();
	void UpdatePickedShape();

	std::vector<glm::vec3> GetVertices(GLfloat* objectData, size_t elements, unsigned int bufferSize);
	std::vector<std::array<glm::vec3, 3>> InitializeTriangles(size_t* indices, int indices_count, Vertices& vertices);
	std::vector<std::array<glm::vec3, 3>> InitializeTriangles(std::vector<int>& indices, Vertices& vertices);
	std::vector<std::vector<std::array<glm::vec3, 3>>> GetFaces(std::vector<std::array<glm::vec3, 3>>& triangles);
	std::vector<std::array<glm::vec3, 2>> GetEdges(GLfloat* objectData);
	void TranslatePoints(glm::mat4& mvp, Vertices& verts);

	std::vector<std::array<glm::vec3, 3>> GetTriangles() const;
	unsigned long Id;


	//shadows for shape
	virtual void GenerateShadow(glm::mat4& lightSpaceMatrix);
	virtual void UpdateLight();

	virtual void AddParamsToShader();

	ShapeParameters shapeParams;
	ShapeElements shapeElements;

	glm::mat4 GetModel() const { return mvp.model; };

	bool Selected = false;
	TextureManager tm;
	ShaderCompiler sc;
	BufferManager* bm;
	ShaderManager* sm;

	std::unique_ptr<ShapesBuilder> builder;
	std::vector<ShaderParams> functionParams;

	virtual ~Shape();

protected:
	virtual void CreateMVPMatrix() {};
	void CreateType();
	void GeneratePickedShaders();
	void PrepareShaderMatricesFieldData();

	VertexManager vm;
	
	std::vector<std::string> paths;

	std::vector<glm::vec3> normals;
	MVP mvp;
	std::string ShapeName;
	glm::vec3 shapeCoords;

	glm::vec3 insideLightPos;
	glm::vec3 camEyePos;

	Physics physics;
	ShapeStateType* type;
	ShapeState shapeState;
	
	Shape* light;
	glm::vec3 mainLight;
	RGB rgbCheck;

	StencilOutline* stencilOutline;

	ShapeType shapeType;

	unsigned int indexesCount = 0;
	std::vector<int> indexes;

	bool deffered = false;

	std::unique_ptr<VerticesShape> verts;
};
