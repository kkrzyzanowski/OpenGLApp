#pragma once

#include "..\Managers\ShaderCompiler.h"
#include "..\glm\glm.hpp"
#include "..\glm\gtc\matrix_transform.hpp"
#include "..\glm\gtc\type_ptr.hpp"

#include "../Shapes/VerticesCreator.h"
#include "../Managers/BufferManager.h"
#include "../MVPManager.h"
#include "../Camera/Camera.h"

class LightBuilder;

class Light
{
public:
	Light();
	Light(const Light&) = default;
	Light(LightBuilder& builder);
	void Create(const GLfloat* points, unsigned int* orderIndex, unsigned int countVertices, unsigned int countIndexes, unsigned int dataSize);
	void Update();
	void GenerateLightShaders();
	void GenerateMVPLight(Camera* camera);
	void CreateModel();
	void LoadLightShaders();
	inline std::vector<ShaderParams> GetParams() { return params; }
	inline glm::vec4 GetColor() { return color; }
	inline glm::vec3 GetPosition() { return Position; }
	glm::vec3 Position;
	glm::mat4 LightProjection;
	glm::mat4 LightView;
	glm::mat4 LightSpaceMatrix;
	BufferManager* bm;
	MVPManager* mvpManager;
	~Light();
protected:
	virtual void GenerateLightShape();
	float nearPlane = 1.0f;
	float farPlane = 10.0f;
	ShaderCompiler* sc;
	ShaderManager* sm;
	ShaderManager* lsm;
	glm::vec4 color;
	VerticesShape* lightSphere;
	float ortographicSize = 10.0f;
	std::vector<ShaderParams> params;
};

