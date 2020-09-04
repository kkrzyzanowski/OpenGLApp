#include "ShapeManager.h"

std::vector<Shape*> ShapeManager::shapes;
ShapesBuilder shapesBuilder;

ShapeManager::ShapeManager()
{
}


void ShapeManager::InsertShape(ShapeType shapeType, SourceShapeType sourceShapeType, CamView camView)
{
	shapes.push_back(shapesBuilder.ObjectState(camView).
		SourceType(sourceShapeType).
		CreateShape(shapeType));
}

ShapeManager::~ShapeManager()
{
}
