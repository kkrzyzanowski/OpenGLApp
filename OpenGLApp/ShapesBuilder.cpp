#include "ShapesBuilder.h"
#include "Cube.h"
#include "Plane.h"
#include "Sphere.h"
#include "SkyBoxCube.h"
#include "CustomShape.h"
#include "Line.h"
#include "Terrain.h"

ShapesBuilder::ShapesBuilder()
{

}

 Shape* ShapesBuilder::CreateShape(const ShapeType shapeType)
{
	 switch (shapeType)
	 {
	 case ShapeType::CUBE:
	 {
		 return new Cube(*this);
	 }
	 case ShapeType::RECTANGLE:
	 {
		 return new Plane(*this);
	 }
	 case ShapeType::SPEHERE:
	 {
		 return new Sphere(*this);
	 }
	 case ShapeType::CUSTOM:
	 {
		 return new CustomShape(*this);
	 }
	 case ShapeType::SKYBOX:
	 {
		 return	new SkyBoxCube(*this);
	 }
	 case ShapeType::LINE:
	 {
		 return new Line();
	 }

	 case ShapeType::TERRAIN:
	 {
		 return new Terrain(*this);
	 }
	 }
	 return new Plane(*this);
}

ShapesBuilder  ShapesBuilder::Light(Shape * light)
{
	m_light = light;
	return *this;
}

ShapesBuilder  ShapesBuilder::SourceType(SourceShapeType shapeType)
{
	m_shapeType = shapeType;
	return *this;
}

ShapesBuilder  ShapesBuilder::ObjectState(CamView view)
{
	m_view = view;
	return *this;
}


ShapesBuilder  ShapesBuilder::OutLight(glm::vec3 pos)
{
	m_pos = pos;
	return *this;
}

ShapesBuilder  ShapesBuilder::LightCast(LightType lightType)
{
	if (m_shapeType == SourceShapeType::LIGHT)
		m_lightType = lightType;
	else
		m_lightType = LightType::NONELIGHT;

	return *this;
}

ShapesBuilder ShapesBuilder::PathModel(std::string path)
{
	m_path = path;
	return *this;
}

ShapesBuilder ShapesBuilder::CustomProperties(TerrainProperties& tp)
{
	this->props = tp;
	return *this;
}




