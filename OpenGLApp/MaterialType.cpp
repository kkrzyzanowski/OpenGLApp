#include "MaterialType.h"
#include "Enums.h"

LightShape::LightShape()
{
}

LightShape::LightShape(LightType lightType)
{
	_LightType = lightType;
	switch (lightType)
	{
			case LightType::DIRECTIONAL:
			{
				light = new LightProps();
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
				light = new LightProps();
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
