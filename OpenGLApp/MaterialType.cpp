#include "MaterialType.h"

LightShape::LightShape()
{
}

LightShape::LightShape(LightType lightType)
{
	m_LightType = lightType;
	switch (lightType)
	{
			case LightType::DIRECTIONAL:
			{
				light = new Light();
				break;
			}
			case LightType::POINT:
			{
				light = new PointLight();
				break;
			}
			case LightType::SPOTLIGHT:
			{
				light = new SpotLight();
				break;
			}
			default:
			{
				light = new Light();
				break;
			}
	}

}

LightShape::~LightShape()
{
}

ShapeStateType::ShapeStateType()
{
}

ShapeStateType::~ShapeStateType()
{
}
