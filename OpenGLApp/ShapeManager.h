#pragma once

#include <vector>
#include "Shape.h"

static class ShapeManager
{
public:
	ShapeManager();
	static std::vector<Shape*> shapes;
	~ShapeManager();
};

