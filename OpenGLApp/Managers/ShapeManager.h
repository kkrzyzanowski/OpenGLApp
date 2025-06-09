#pragma once
#include <vector>
#include <memory>
#include "..\Shapes\Shape.h"

class Camera;

static class ShapeManager
{
public:
	ShapeManager();
	static std::vector<std::shared_ptr<Shape>> shapes;
	//static void InsertShape(ShapeType shapeType, SourceShapeType sourceShapeType, CamView camView);
	static void InitializeShapesData(Camera* cam);
	static std::shared_ptr<ShapesBuilder> shapesBuilder;
	static void AddShape(ShapeType type);
	static std::vector<std::shared_ptr<Shape>> FilterShape(Shading shadingType);
	static std::vector<std::shared_ptr<Shape>> FilterShape(bool shadow);
	~ShapeManager();
private:
};

