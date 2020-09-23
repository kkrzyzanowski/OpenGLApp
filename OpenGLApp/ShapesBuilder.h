#pragma once
#include <memory>
#include "Shape.h"
#include "CustomProperties.h"
#include "ShapeList.h"

class ShapesBuilder
{
public:
	ShapesBuilder();
	std::shared_ptr<Shape> CreateShape(const ShapeType shapeType);
	ShapesBuilder Light(Shape* light);
	ShapesBuilder SourceType(SourceShapeType shapeType);
	ShapesBuilder ObjectState(CamView view);
	ShapesBuilder OutLight(glm::vec3 pos);
	ShapesBuilder LightCast(LightType lightType);
	ShapesBuilder PathModel(std::string path);
	ShapesBuilder Position(glm::vec3 position);
	ShapesBuilder Rotation(glm::vec3 position);
	ShapesBuilder CustomProperties(TerrainProperties& tp);
	std::shared_ptr<Shape> m_shape;
	SourceShapeType m_shapeType;
	Shape* m_light;
	CamView m_view;
	glm::vec3 m_pos;
	LightType m_lightType;
	std::string m_path;
	TerrainProperties props;
	ShapeType m_type;

};
