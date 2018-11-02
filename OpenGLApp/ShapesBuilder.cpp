#include "ShapesBuilder.h"
#include "Cube.h"
#include "Plane.h"
#include "Sphere.h"
ShapesBuilder::ShapesBuilder()
{

}

 Shape* ShapesBuilder::CreateShape(const Shapes shapeType)
{
	 switch (shapeType)
	 {
	 case Shapes::CUBE:
	 {
		 return new Cube(*this);
	 }
	 case Shapes::RECTANGLE:
	 {
		 return new Plane(*this);
	 }
	 case Shapes::SPEHERE:
	 {
		 return new Sphere(*this);
	 }
	 case Shapes::TRIANGLE:
	 {
		 break;
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




