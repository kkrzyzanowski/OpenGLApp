#include "ShapesBuilder.h"
#include "..\Shapes\Cube.h"
#include "..\Shapes\Plane.h"
#include "..\Shapes\Sphere.h"
#include "..\Shapes\SkyBoxCube.h"
#include "..\Shapes\CustomShape.h"
#include "..\Shapes\Line.h"
#include "..\Shapes\Terrain.h"

namespace AppEngine
{
	ShapesBuilder::ShapesBuilder(ShapesBuilder&& other) noexcept
		: _shapes(std::move(other._shapes))
		, _light(other._light)
		, View(other.View)
		, _lightType(other._lightType)
		, _path(std::move(other._path))
		, texturePaths(std::move(other.texturePaths))
		, shaderPaths(std::move(other.shaderPaths))
		, _props(std::move(other._props))
		, _type(other._type)
		, ShadingType(other.ShadingType)
		, Func(std::move(other.Func))
		, IsShadowActive(other.IsShadowActive)
		, IsBloomActive(other.IsBloomActive)
		, HDR(other.HDR)
	{
		// move/copy pola z bazowego Builder (s¹ publiczne)
		Pos = other.Pos;
		Axis = other.Axis;
		ScaleVector = other.ScaleVector;
		Angle = other.Angle;
		color = other.color;
		// SourceShapeType (Builder::Type) — kopiujemy
		Type = other.Type;

		// Leave 'other' in a valid default state
		other._light = nullptr;
		other.texturePaths.clear();
		other.shaderPaths.clear();
		other._path.clear();
		other._props = TerrainProperties();            // reset to default
		other._type = ShapeType();                     // default-constructed
		other.Func = ShaderFunction();                 // empty std::function
		other.ShadingType = Shading::FORWARD_SHADING;
		other.IsShadowActive = false;
		other.IsBloomActive = false;
		other.HDR = false;
		other.ScaleVector = glm::vec3(1.0f);
		other.Pos = glm::vec3(0.0f);
		other.Axis = glm::vec3(0.0f);
		other.Angle = 0.0f;
		other.color = glm::vec4(1.0f);
		other.Type = SourceShapeType();                // safe default
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
			this->IsBloomActive = other.IsBloomActive;
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

	ShapesBuilder& ShapesBuilder::PathModel(const std::string& path)
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
		std::cout << path << " " << "-path" << std::endl;
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

	ShapesBuilder& ShapesBuilder::Bloom(bool bloom)
	{
		IsBloomActive = bloom;
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
		case Shading::BLOOM:
		{
			Func = ShaderTypeGenerator::BloomShaderGenerator;
			break;
		}

		}
	}
}
