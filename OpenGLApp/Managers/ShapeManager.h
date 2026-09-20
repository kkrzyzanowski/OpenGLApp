#pragma once
#include <vector>
#include <memory>
#include "..\Shapes\Shape.h"

namespace AppEngine
{
	class Camera;

	static class ShapeManager
	{
		//static void InsertShape(ShapeType shapeType, SourceShapeType sourceShapeType, CamView camView);
	public:
		ShapeManager();
		static void InitializeShapesData(Camera* cam);
		static void InitializeShapeData(std::shared_ptr<Shape> shape, Camera* cam);
		static std::shared_ptr<Shape> AddShape(ShapeType type, float position[4], float color[4], float rotation[3], float scale[3], const std::string& filePath);
		static std::vector<std::shared_ptr<Shape>> FilterShape(Shading shadingType);
		static std::vector<std::shared_ptr<Shape>> FilterShape(std::initializer_list<Shading> shadingTypes);
		static std::vector<std::shared_ptr<Shape>> FilterShape(ShapeType type);
		static std::vector<std::shared_ptr<Shape>> GetShapesWithShadow();
		~ShapeManager();

	public:
		static std::vector<std::shared_ptr<Shape>> shapes;
		static std::shared_ptr<ShapesBuilder> shapesBuilder;
	private:
	};
}
