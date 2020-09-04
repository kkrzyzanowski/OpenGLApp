#include "Physics.h"



Physics::Physics()
{
	mass = 1.0f;
	velocity = glm::vec3(1.0f, 1.0f, 1.0f);
	acceleration = 1.0f;
	drag = 0.0f;
	gravity = true;
	gravityValue = glm::vec3(0.0f, 10.0f, 0.0f);
}


Physics::~Physics()
{
}

Physics::Physics(float m, glm::vec3 v, float a , float d, bool g, glm::vec3 gv)
{
	mass = m;
	velocity = v;
	acceleration = a;
	drag = d;
	gravity = g;
	gravityValue = gv;
}
