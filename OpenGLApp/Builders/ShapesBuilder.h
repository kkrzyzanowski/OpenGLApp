#pragma once
#include "Builder.h"
#include "..\CustomProperties.h"
#include "..\Shaders\ShaderClasses\Shader.h"
#include "..\Shaders\ShaderClasses\ShaderTypeGenerator.h"
#include "..\DataStructures.h"
class Shape;

class ShapesBuilder: public Builder<Shape, ShapeType>
{
public:
	ShapesBuilder() = default;
	ShapesBuilder(ShapesBuilder&& other) noexcept;
	ShapesBuilder(const ShapesBuilder&& other) noexcept;
	ShapesBuilder(const ShapesBuilder& other) noexcept;
	ShapesBuilder(ShapesBuilder& other) noexcept;
	ShapesBuilder& operator=(ShapesBuilder&& other) noexcept;
	ShapesBuilder& operator=(const ShapesBuilder& other) noexcept;
	~ShapesBuilder() = default;
	std::shared_ptr<Shape> Create(const ShapeType shapeType) override;
	ShapesBuilder& Light(Shape* light);
	ShapesBuilder& ObjectState(CamView view);
	ShapesBuilder& OutLight(glm::vec3 pos);
	ShapesBuilder& LightCast(LightType lightType);
	ShapesBuilder& PathModel(std::string path);
	ShapesBuilder& CustomProperties(TerrainProperties& tp);
	ShapesBuilder& SourceType(SourceShapeType shapeType);
	ShapesBuilder& Texture(const char* path);
	ShapesBuilder& Texture(const std::string& path);
	ShapesBuilder& Shader(const char* path);
	ShapesBuilder& Shader(const std::string& path);
	ShapesBuilder& SetShading(Shading shading);
	ShapesBuilder& Shadow(bool shadow);
	ShapesBuilder& Bloom(bool bloom);
	ShapesBuilder& SetHDR(bool hdr);
	std::shared_ptr<Shape> _shapes;
	Shape* _light;
	CamView View;
	LightType _lightType;
	std::string _path;
	std::vector<const char*> texturePaths;
	std::vector<const char*> shaderPaths;
	TerrainProperties _props;
	ShapeType _type;
	Shading ShadingType = Shading::FORWARD_SHADING;
	ShaderFunction Func;
	bool IsShadowActive;
	bool IsBloomActive;
	bool HDR;
private:

	void CheckShadingType();

};
