#include <algorithm>
#include "ShapeManager.h"
#include "..\Builders\ShapesBuilder.h"
#include "..\Lights\Light.h"
#include "LightManager.h"
#include "..\Camera\Camera.h"

namespace AppEngine
{
	std::vector<std::shared_ptr<Shape>> ShapeManager::shapes;

	//ShapesBuilder shapesBuilder;
	std::shared_ptr<ShapesBuilder> ShapeManager::shapesBuilder = std::make_shared<ShapesBuilder>();
	ShapeManager::ShapeManager()
	{
	}


	//void ShapeManager::InsertShape(ShapeType shapeType, SourceShapeType sourceShapeType, CamView camView)
	//{
	//	shapes.push_back(shapesBuilder.ObjectState(camView).
	//		SourceType(sourceShapeType).
	//		Create(shapeType));
	//}

	void ShapeManager::InitializeShapesData(Camera* cam)
	{
		for (auto& shape : ShapeManager::shapes)
		{
			InitializeShapeData(shape, cam);
		}
	}

	void ShapeManager::InitializeShapeData(std::shared_ptr<Shape> shape, Camera* cam)
	{
		std::vector<ShaderParams> params;
		LightManager::InitializeShadowProgram(shape);
		shape->ApplyShapeView(cam->GetView());
		shape->ApplyProjectionMatrix(cam->GetProjection());
		shape->SetEyeCamPos(cam->GetCamPos());
		shape->SetMainLight(LightManager::lights[0]->Position);
		shape->GenerateShaders();
		LightManager::PassLightDataToShape(shape);
		LightManager::ApplyHDRLightParams(shape, params);
		shape->PassShaderParams(params);
		shape->ApplyShaders();
		shape->DeactivateShapeBufferParts();
		shape->InitializePickedShape();
	}


	std::shared_ptr<Shape> ShapeManager::AddShape(ShapeType type, float position[4], float color[4], float rotation[3], float scale[3], const std::string& filePath)
	{
		auto& shape = shapes.emplace_back(shapesBuilder->ObjectState(CamView::DYNAMIC)
			.SourceType(SourceShapeType::SHAPE)
			.Shader(PRIMITIVE_VERT_PATH)
			.Shader(PRIMITIVE_FRAG_PATH)
			.PathModel(filePath)
			.SetShading(Shading::ONLY_COLOR)
			.Position(glm::vec3(position[0], position[1], position[2]))
			.Color(glm::vec4(color[0], color[1], color[2], color[3]))
			.Rotation(glm::vec3(rotation[0], rotation[1], rotation[2]), 0.0f)
			.Scale(glm::vec3(scale[0], scale[1], scale[2]))
			.Create(type));
		return shape;
	}



	std::vector<std::shared_ptr<Shape>> ShapeManager::FilterShape(Shading shadingType)
	{
		std::vector<std::shared_ptr<Shape>> filteredShapes;
		std::copy_if(
			shapes.begin(), shapes.end(),
			std::back_inserter(filteredShapes),
			[&shadingType](const std::shared_ptr<Shape>& shape) {
				return shape->GetShading() == shadingType;
			});
		return filteredShapes;
	}

	std::vector<std::shared_ptr<Shape>> ShapeManager::FilterShape(std::initializer_list<Shading> shadingTypes)
	{
		std::vector<std::shared_ptr<Shape>> filteredShapes;
		std::copy_if(
			shapes.begin(), shapes.end(),
			std::back_inserter(filteredShapes),
			[shadingTypes](const std::shared_ptr<Shape>& shape) {
				Shading shapeShading = shape->GetShading();
				int shapeVal = static_cast<int>(shapeShading);
				for (auto flag : shadingTypes)
				{
					int flagVal = static_cast<int>(flag);
					if ((shapeVal & flagVal) != 0) // matches any provided flag
						return true;
				}
				return false;
			});
		return filteredShapes;
	}

	std::vector<std::shared_ptr<Shape>> ShapeManager::FilterShape(ShapeType type)
	{
		std::vector<std::shared_ptr<Shape>> filteredShapes;
		std::copy_if(
			shapes.begin(), shapes.end(),
			std::back_inserter(filteredShapes),
			[&type](const std::shared_ptr<Shape>& shape) {
				return shape->GetType() == type;
			});
		return filteredShapes;
	}

	std::vector<std::shared_ptr<Shape>> ShapeManager::GetShapesWithShadow()
	{
		std::vector<std::shared_ptr<Shape>> filteredShapes;
		std::copy_if(
			shapes.begin(), shapes.end(),
			std::back_inserter(filteredShapes),
			[](const std::shared_ptr<Shape>& shape) {
				return shape->IsShadowTurnOn();
			});
		return filteredShapes;
	}

	ShapeManager::~ShapeManager()
	{
	}
}
