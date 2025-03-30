#include "LightBuilder.h"

std::shared_ptr<Light> LightBuilder::Create(const LightType lightType)
{
	return std::make_shared<Light>(*this);
}

LightBuilder::LightBuilder(LightBuilder& other)
{
	if (this != &other)
	{
		
		this->Pos = other.Pos;
		this->color = other.color;
		this->NearPlane = other.NearPlane;
		this->FarPlane = other.FarPlane;
		this->Size = other.Size;

	}
}

LightBuilder::LightBuilder(LightBuilder&& other)
{
	this->Pos = std::move(other.Pos);
	this->color = std::move(other.color);
	this->NearPlane = std::move(other.NearPlane);
	this->FarPlane = std::move(other.FarPlane);
	this->Size = std::move(other.Size);
	other.NearPlane = 1.0f;
	other.FarPlane = 10.0f;
	other.Size = 10.0f;
}

LightBuilder& LightBuilder::SetColor(glm::vec4& color)
{
	Color = color;
	return *this;
}

LightBuilder& LightBuilder::SetColor(glm::vec4&& color)
{
	Color = std::move(color);
	return *this;
}

