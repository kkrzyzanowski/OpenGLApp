#pragma once

struct VerticesShape
{
	void operator()(VerticesShape* shape) const 
	{
		delete[] shape->Points;
		delete[] shape->Indexes;
		delete shape;
	}
	unsigned int PointsCount;
	unsigned int IndexesCount;
	float* Points;
	unsigned int* Indexes;
};


VerticesShape* CreateSphere(int rings, int sectors, unsigned short bufferSize, float radius = 1.0f); 
VerticesShape* CreateCube(float size = 1.0f, unsigned int bufferSize = 8); 
VerticesShape* CreatePlane(float size = 1.0f); 
VerticesShape* CreateQuad();