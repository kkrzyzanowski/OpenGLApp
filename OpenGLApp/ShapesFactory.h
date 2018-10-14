#pragma once
#include "Shape.h"
enum Shapes
{
		TRIANGLE = 9, RECTANGLE = 12, CUBE = 36, SPEHERE = 10
};
class ShapesFactoryPrototype
{
public:
	virtual Shape* CreateShape(const Shapes shapeType) = 0 {};
protected:
		Shape* shape;

};

class ShapeCreator : ShapesFactoryPrototype
{
public:
	Shape* CreateShape(const Shapes shapeType) override;
};