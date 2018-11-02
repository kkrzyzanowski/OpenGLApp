#pragma once
#include "Shape.h"

enum Shapes
{
		TRIANGLE = 9, RECTANGLE = 12, CUBE = 36, SPEHERE = 10
};
static class ShapesBuilder
{
public:
	ShapesBuilder();
	 Shape* CreateShape(const Shapes shapeType);
	 ShapesBuilder Light(Shape* light);
	 ShapesBuilder SourceType(SourceShapeType shapeType);
	 ShapesBuilder ObjectState(CamView view);
	 ShapesBuilder OutLight(glm::vec3 pos);
	 ShapesBuilder LightCast(LightType lightType);
	Shape* m_shape;
	SourceShapeType m_shapeType;
	Shape* m_light;
	CamView m_view;
	glm::vec3 m_pos;
	LightType m_lightType;
};
