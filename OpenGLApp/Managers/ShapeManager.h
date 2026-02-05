#pragma once
#include <vector>
#include <memory>
#include "..\Shapes\Shape.h"

class Camera;

static class ShapeManager
{
	//static void InsertShape(ShapeType shapeType, SourceShapeType sourceShapeType, CamView camView);
public:
	ShapeManager();
	static void InitializeShapesData(Camera* cam);
	static void AddShape(ShapeType type);
	static std::vector<std::shared_ptr<Shape>> FilterShape(Shading shadingType);
	static std::vector<std::shared_ptr<Shape>> FilterShape(std::initializer_list<Shading> shadingTypes);
	static std::vector<std::shared_ptr<Shape>> FilterShape(bool shadow);
	~ShapeManager();

public:
	static std::vector<std::shared_ptr<Shape>> shapes;
	static std::shared_ptr<ShapesBuilder> shapesBuilder;
private:
};

