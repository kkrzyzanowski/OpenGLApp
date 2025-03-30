#pragma once
#include <vector>
#include "..\Shapes\Shape.h"
class Collision
{
public:

	Collision();
	void AddShapeCollision(Shape* shape);
	void RemoveShapeCollision(std::string& id);
	bool CheckCollision();
	bool CheckShapeCollision();
	~Collision();

	std::vector<std::shared_ptr<Shape>> objects;
};

