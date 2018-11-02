#define GLM_ENABLE_EXPERIMENTAL
#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtc\type_ptr.hpp"
#pragma once
class ShapeType
{
public:
	ShapeType();
	~ShapeType();
protected:

};


enum LightType
{
	DEFAULT = 0,
	DIRECTIONAL = 1,
	POINT = 2,
	SPOTLIGHT = 3,
	NONELIGHT = 4,
};

struct Light
{
public:
	glm::vec3 m_LightPos;
	glm::vec3 m_LightDirection;
	glm::vec3 m_LightColor;
};
struct PointLight : Light
{
public:
	glm::vec3 constant;
	glm::vec3 linear;
	glm::vec3 quadratic;
};
struct SpotLight: Light
{
public:
	float cutOff;
	float outerCutOff;
};
class LightShape : public ShapeType
{
public:
	LightShape();
	LightShape(LightType lightType);
	~LightShape();
private:
	LightType m_LightType;
	Light* light;
};

class DiffuseShape : public ShapeType
{
private:
	LightShape * m_SourceLight;
};
class ParticleShape : public ShapeType
{

};

class MaterialTypeCreator
{
public:
	ShapeType * GetType();
private:
	ShapeType* type;
};