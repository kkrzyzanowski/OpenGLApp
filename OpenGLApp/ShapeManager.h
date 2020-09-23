#pragma once

#include <vector>
#include <memory>
#include "Shape.h"
#include "ShapesBuilder.h"

static class ShapeManager
{
public:
	ShapeManager();
	static std::vector<std::shared_ptr<Shape>> shapes;
	static void InsertShape(ShapeType shapeType, SourceShapeType sourceShapeType, CamView camView);
	~ShapeManager();
};

