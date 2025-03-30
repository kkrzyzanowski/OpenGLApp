#pragma once
#include <memory>
#include "..\glm\glm.hpp"
#include "..\glm\gtc\type_ptr.hpp"
#include "..\ShapeType.h"

template <typename T, typename U>
class Builder
{
public:
	Builder() = default;
	~Builder() = default;


	Builder<T, U>& Position(glm::vec3& position)
	{
		Pos = position;
		return *this;
	}


	Builder<T, U>& Position(glm::vec3&& position)
	{
		Pos = std::move(position);
		return *this;
	}

	
	Builder<T, U>& Rotation(glm::vec3& axis, float angle)
	{
		this->Angle = angle;
		this->Axis = axis;
		return *this;
	}
	Builder<T, U>& Rotation(glm::vec3&& axis, float angle)
	{
		this->Angle = angle;
		this->Axis = std::move(axis);
		return *this;
	}

	Builder<T, U>& Scale(glm::vec3& scale)
	{
		this->ScaleVector = scale;
		return *this;
	}

	Builder<T, U>& Scale(glm::vec3&& scale)
	{
		this->ScaleVector = std::move(scale);
		return *this;
	}

	Builder<T, U>& Color(glm::vec4& color)
	{
		this->color = color;
		return *this;
	}
	Builder<T, U>& Color(glm::vec4&& color)
	{
		this->color = std::move(color);
		return *this;
	}

	virtual std::shared_ptr<T> Create(const U type) = 0;
	glm::vec3 Pos;
	glm::vec3 Axis;
	glm::vec3 ScaleVector = glm::vec3(1.0f);
	float Angle;
	SourceShapeType Type;
	glm::vec4 color;
};



