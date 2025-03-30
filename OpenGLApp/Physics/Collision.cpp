#include <cmath>
#include "Collision.h"
#include "..\Shapes\Sphere.h"
#include "..\Shapes\Plane.h"

Collision::Collision()
{
}

void Collision::AddShapeCollision(Shape * shape)
{
}

void Collision::RemoveShapeCollision(std::string & id)
{
}

bool Collision::CheckCollision()
{
	for(int i = 0; i<objects.size(); i++)
	{
		for (int j = 0; j < objects.size(); j++)
		{
			if (dynamic_cast<Sphere*>(objects[i].get()) != nullptr && dynamic_cast<Plane*>(objects[j].get()) != nullptr && i != j)
			{
				Sphere* sphere = dynamic_cast<Sphere*>(objects[i].get());
				Plane* plane = dynamic_cast<Plane*>(objects[j].get());

				glm::vec3 spherePos = glm::vec3(sphere->GetPosition()[0], sphere->GetPosition()[1], sphere->GetPosition()[2]);
				glm::vec3 planePos = glm::vec3(plane->GetPosition()[0], plane->GetPosition()[1], plane->GetPosition()[2]);
				float sphereRadius = sphere->GetRadius();


				size_t planeTriangles = plane->shapeElements.triangles.size();

				for (int i = 0; i < planeTriangles; i++)
				{
					glm::vec3 v1 = plane->shapeElements.triangles[i][0];
					glm::vec3 v2= plane->shapeElements.triangles[i][1];
					glm::vec3 v3 = plane->shapeElements.triangles[i][2];

					glm::vec3 vNormal = plane->shapeParams.normals[i];

					float equation = -glm::dot(planePos, vNormal);
					float distance = glm::dot(spherePos, vNormal) + equation;

					//std::cout << "Distance to plane is equal: " << distance << std::endl;
					if (distance <= sphereRadius)
					{
						return true;
					}
					/*glm::vec3 verticesAvg = (v1 + v2 + v3) / 3.0f;
					float d = -glm::dot(verticesAvg, vNormalized);

					float distanceToSphere = glm::dot(vNormalized, spherePos) + d;

					if (fabs(distanceToSphere) > sphereRadius)
					{
						continue;
					}
					
					glm::vec3 AB = v2 - v1;
					glm::vec3 AC = v3 - v1;
					glm::vec3 BC = v3 - v2;

					glm::vec3 planeX = glm::normalize(AB);
					glm::vec3 planeY = glm::normalize(glm::cross(vNormalized, AB));

					auto project2d = [&](const glm::vec3 &p) {return glm::vec2(glm::dot(p, planeX), glm::dot(p, planeY)); };

					glm::vec2 planePos2d = project2d(spherePos);
					std::array<glm::vec2, 3> trinagle2D = { project2d(v1), project2d(v2), project2d(v3) };*/
				}

			}
		}
	}
	return false;
}

bool Collision::CheckShapeCollision()
{
	return false;
}


Collision::~Collision()
{
}
