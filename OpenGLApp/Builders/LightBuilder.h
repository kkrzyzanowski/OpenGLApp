#pragma once
#include "Builder.h"
#include "../Lights/Light.h"

class LightBuilder : public Builder<Light, LightType>
{
public:
	LightBuilder() = default;
	~LightBuilder() = default;
	LightBuilder(LightBuilder& other);
	LightBuilder(LightBuilder&& other);
	LightBuilder& SetColor(glm::vec4& color);
	LightBuilder& SetColor(glm::vec4&& color);
	std::shared_ptr<Light> Create(const LightType lightType) override;
	std::shared_ptr<Light> _lights;
	glm::vec4 Color;
	float NearPlane = 1.0f;
	float FarPlane = 10.0f;
	float Size = 10.0f;
private:
};

