#include "ShapesBuilder.h"
#include "..\Shapes\Cube.h"
#include "..\Shapes\Plane.h"
#include "..\Shapes\Sphere.h"
#include "..\Shapes\SkyBoxCube.h"
#include "..\Shapes\CustomShape.h"
#include "..\Shapes\Line.h"
#include "..\Shapes\Terrain.h"


ShapesBuilder::ShapesBuilder(ShapesBuilder&& other) noexcept
{
	this->texturePaths = std::move(other.texturePaths);
	this->shaderPaths = std::move(other.shaderPaths);
	this->Pos = std::move(other.Pos);
	this->Func = std::move(other.Func);
	this->View = std::move(other.View);
	this->color = std::move(other.color);
	this->Angle = std::move(other.Angle);
	this->Axis = std::move(other.Axis);
	this->Type = std::move(other.Type);
	this->ShadingType = std::move(other.ShadingType);
	this->_path = std::move(other._path);
	this->IsShadowActive = other.IsShadowActive;
	this->ScaleVector = other.ScaleVector;
	this->HDR = other.HDR;
	other.texturePaths.clear();
	other.shaderPaths.clear();
	other.ShadingType = Shading::FORWARD_SHADING;
	other.IsShadowActive = false;
	other.HDR = false;
	other.ScaleVector = glm::vec3(1.0f);
}

ShapesBuilder::ShapesBuilder(const ShapesBuilder& other) noexcept
{
	if (this != &other)
	{
		texturePaths = other.texturePaths;
		shaderPaths = other.shaderPaths;
		_path = other._path;
		ShadingType = other.ShadingType;
		Func = other.Func;
		this->Pos = other.Pos;
		this->Func = other.Func;
		this->View = other.View;
		this->color = other.color;
		this->Angle = other.Angle;
		this->Axis = other.Axis;
		this->Type = other.Type;
		this->ShadingType = other.ShadingType;
		this->IsShadowActive = other.IsShadowActive;
		this->HDR = other.HDR;
	}
}

ShapesBuilder& ShapesBuilder::operator=(ShapesBuilder&& other) noexcept
{
	if (this != &other)
	{
		texturePaths.clear();
		shaderPaths.clear();
		_path = "";
		ShadingType = Shading::FORWARD_SHADING;
		Func = nullptr;
	}
	return *this;
}

ShapesBuilder& ShapesBuilder::operator=(const ShapesBuilder& other) noexcept
{
	if (this != &other)
	{
		texturePaths = other.texturePaths;
		shaderPaths = other.shaderPaths;
		_path = other._path;
		ShadingType = other.ShadingType;
		Func = other.Func;
	}
	return *this;
}

std::shared_ptr<Shape> ShapesBuilder::Create(const ShapeType shapeType)
{
	_type = shapeType;
	CheckShadingType();

	switch (shapeType)
	{
	case ShapeType::CUBE:
	{
		return std::make_shared<Cube>(std::move(*this));
	}
	case ShapeType::PLANE:
	{
		return std::make_shared<Plane>(std::move(*this));
	}
	case ShapeType::SPEHERE:
	{
		return std::make_shared<Sphere>(std::move(*this));
	}
	case ShapeType::CUSTOM:
	{
		return std::make_shared<CustomShape>(std::move(*this));
	}
	case ShapeType::SKYBOX:
	{
		return std::make_shared<SkyBoxCube>(std::move(*this));
	}
	case ShapeType::LINE:
	{
		return std::make_shared<Line>(std::move(*this));
	}

	case ShapeType::TERRAIN:
	{
		Func = ShaderTypeGenerator::InstancedTerrainShaderGenerator;
		return std::make_shared<Terrain>(std::move(*this));
	}
	}
	return std::make_shared<Plane>(std::move(*this));

}

ShapesBuilder& ShapesBuilder::Light(Shape* light)
{
	_light = light;
	return *this;
}

ShapesBuilder& ShapesBuilder::ObjectState(CamView view)
{
	View = view;
	return *this;
}


ShapesBuilder& ShapesBuilder::OutLight(glm::vec3 pos)
{
	Pos = pos;
	return *this;
}

ShapesBuilder& ShapesBuilder::LightCast(LightType lightType)
{
	if (Type == SourceShapeType::LIGHT)
		_lightType = lightType;
	else
		_lightType = LightType::NONELIGHT;

	return *this;
}

ShapesBuilder& ShapesBuilder::PathModel(std::string path)
{
	_path = path;
	return *this;
}

ShapesBuilder& ShapesBuilder::CustomProperties(TerrainProperties& tp)
{
	this->_props = tp;
	return *this;
}

ShapesBuilder& ShapesBuilder::SourceType(SourceShapeType shapeType)
{
	Type = shapeType;
	return *this;
}

ShapesBuilder& ShapesBuilder::Texture(const char* path)
{
	texturePaths.push_back(path);
	return *this;
}

ShapesBuilder& ShapesBuilder::Texture(const std::string& path)
{
	texturePaths.push_back(path.c_str());
	return *this;
}


ShapesBuilder& ShapesBuilder::Shader(const char* path)
{
	std::cout <<  path << " " << "-path" << std::endl;
	shaderPaths.push_back(path);
	return *this;
}

ShapesBuilder& ShapesBuilder::Shader(const std::string& path)
{
	std::cout << "Shader path: " + path << std::endl;
	shaderPaths.push_back(path.c_str());
	return *this;
}

ShapesBuilder& ShapesBuilder::SetShading(Shading shading)
{
	ShadingType = shading;
	return *this;
}

ShapesBuilder& ShapesBuilder::Shadow(bool shadow)
{
	IsShadowActive = shadow;
	return *this;
}

ShapesBuilder& ShapesBuilder::SetHDR(bool hdr)
{
	HDR = hdr;
	return *this;
}

void ShapesBuilder::CheckShadingType()
{
	switch (ShadingType)
	{
	case Shading::DEFFERED_SHADING:
	{
		Func = ShaderTypeGenerator::GBuffer;
		break;
	}
	case Shading::FORWARD_SHADING:
	{
		Func = ShaderTypeGenerator::ShaderDiffuseGenerator;
		break;
	}
	case Shading::ONLY_COLOR:
	{
		Func = ShaderTypeGenerator::UpdateColorParam;
		break;
	}
	case Shading::TEXTURE_COLOR:
	{
		Func = ShaderTypeGenerator::UpdateModelColorandTexture;
		break;
	}
	case Shading::DISPLACEMENT:
	{
		Func = ShaderTypeGenerator::ShaderDisplacementGenerator;
		break;
	}
	case Shading::HDR_SHADING:
	{
		Func = ShaderTypeGenerator::UpdateLightiningHDR;
		break;
	}
	}
}




