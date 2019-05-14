#pragma once
#include "Shape.h"

enum Shapes
{
		TRIANGLE, RECTANGLE, CUBE, SPEHERE, CUBEBOX, CUSTOM
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
	 ShapesBuilder PathModel(std::string path);
	 ShapesBuilder Position(glm::vec3 position);
	 ShapesBuilder Rotation(glm::vec3 position);
	Shape* m_shape;
	SourceShapeType m_shapeType;
	Shape* m_light;
	CamView m_view;
	glm::vec3 m_pos;
	LightType m_lightType;
	std::string m_path;
};
