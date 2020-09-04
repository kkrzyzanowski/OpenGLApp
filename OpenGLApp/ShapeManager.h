#pragma once

#include <vector>
#include "Shape.h"
#include "ShapesBuilder.h"

static class ShapeManager
{
public:
	ShapeManager();
	static std::vector<Shape*> shapes;
	static void InsertShape(ShapeType shapeType, SourceShapeType sourceShapeType, CamView camView);
	~ShapeManager();
};

