#include "ShapesFactory.h"
#include "Sphere.h"
#include "Plane.h"
Shape* ShapeCreator::CreateShape(const Shapes shapeType)
{
	switch (shapeType)
	{
		case Shapes::SPEHERE:
		{
			shape = new Sphere();
			break;
		}
		case Shapes::RECTANGLE:
		{
			shape = new Plane();
			break;
		}
		default:
			shape = new Sphere();
	}
	return shape;
}
