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


 std::shared_ptr<Shape> ShapesBuilder::CreateShape(const ShapeType shapeType)
{
	 m_type = shapeType;
	 switch (shapeType)
	 {
	 case ShapeType::CUBE:
	 {
		 return std::make_shared<Cube>(*this);
	 }
	 case ShapeType::RECTANGLE:
	 {
		 return std::make_shared<Plane>(*this); 
	 }
	 case ShapeType::SPEHERE:
	 {
		 return std::make_shared<Sphere>(*this);
	 }
	 case ShapeType::CUSTOM:
	 {
		 return std::make_shared<CustomShape>(*this);
	 }
	 case ShapeType::SKYBOX:
	 {
		 return std::make_shared<SkyBoxCube>(*this);
	 }
	 case ShapeType::LINE:
	 {
		 return std::make_shared<Line>();
	 }

	 case ShapeType::TERRAIN:
	 {
		 return std::make_shared<Terrain>(*this);
	 }
	 }
	 return std::make_shared<Plane>(*this);

}

ShapesBuilder ShapesBuilder::Light(Shape * light)
{
	m_light = light;
	return *this;
}

ShapesBuilder ShapesBuilder::SourceType(SourceShapeType shapeType)
{
	m_shapeType = shapeType;
	return *this;
}

ShapesBuilder ShapesBuilder::ObjectState(CamView view)
{
	m_view = view;
	return *this;
}


ShapesBuilder ShapesBuilder::OutLight(glm::vec3 pos)
{
	m_pos = pos;
	return *this;
}

ShapesBuilder ShapesBuilder::LightCast(LightType lightType)
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

ShapesBuilder ShapesBuilder::Position(glm::vec3 position)
{
	// TODO: insert return statement here
	return *this;
}

ShapesBuilder ShapesBuilder::Rotation(glm::vec3 position)
{
	// TODO: insert return statement here
	return *this;
}

ShapesBuilder ShapesBuilder::CustomProperties(TerrainProperties& tp)
{
	this->props = tp;
	return *this;
}




