#include "ShapeManager.h"
#include "..\Builders\ShapesBuilder.h"
#include "..\Lights\Light.h"
#include "LightManager.h"
#include "..\Camera\Camera.h"

std::vector<std::shared_ptr<Shape>> ShapeManager::shapes;
//ShapesBuilder shapesBuilder;
std::shared_ptr<ShapesBuilder> shapesBuilder = std::make_shared<ShapesBuilder>();
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
}


void ShapeManager::AddShape(ShapeType type)
{
	//shapes.push_back(shapesBuilder->Create(type));
}

std::vector<std::shared_ptr<Shape>> ShapeManager::FilterShape(Shading shadingType)  
{  
   std::vector<std::shared_ptr<Shape>> filteredShapes;  
   for (const auto& shape : shapes)  
   {  
       if (shape->GetShading() != shadingType)  
       {  
           filteredShapes.push_back(shape);  
       }  
   }  
   return filteredShapes;  
}  

std::vector<std::shared_ptr<Shape>> ShapeManager::FilterShape(bool shadow)
{  
   static std::vector<std::shared_ptr<Shape>> filteredShapes;  
   filteredShapes.clear();  
   for (const auto& shape : shapes)  
   {  
       if (shape->IsShadowTurnOn() == shadow)  
       {  
           filteredShapes.push_back(shape);  
       }  
   }  
   return filteredShapes;  
}

ShapeManager::~ShapeManager()
{
}
