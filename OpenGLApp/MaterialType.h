#pragma once
#define GLM_ENABLE_EXPERIMENTAL
#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtc\type_ptr.hpp"
#include "ShapeType.h"

class ShapeStateType
{
public:
	ShapeStateType();
	~ShapeStateType();
protected:

};


struct LightProps
{
public:
	glm::vec3 m_LightPos;
	glm::vec3 m_LightDirection;
	glm::vec3 m_LightColor;
};
struct PointLight : LightProps
{
public:
	glm::vec3 constant;
	glm::vec3 linear;
	glm::vec3 quadratic;
};
struct SpotLight: LightProps
{
public:
	float cutOff;
	float outerCutOff;
};
class LightShape : public ShapeStateType
{
public:
	LightShape();
	LightShape(LightType lightType);
	~LightShape();
private:
	LightType _LightType;
	LightProps* light;
};

class DiffuseShape : public ShapeStateType
{
private:
	LightShape* _SourceLight;
};
class ParticleShape : public ShapeStateType
{

};

class MaterialTypeCreator
{
public:
	ShapeStateType * GetType();
private:
	ShapeStateType* type;
};