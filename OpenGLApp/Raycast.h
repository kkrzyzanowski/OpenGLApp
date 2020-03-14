#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtc\type_ptr.hpp"

class Raycast
{
public:
	Raycast(double xPos, double yPos, unsigned int distance, glm::mat4 projection, glm::mat4 view);
	void InverseToEyeCoords();
	void InverseToWorldCoords();
	void CalculateMouseRay();
	bool IntersectionInRange(float start, float end);
	glm::vec3 GetPointFromRay(glm::vec3 ray, float distance);
	glm::vec3 GetWorldRay();

	~Raycast();
private:
	unsigned int rayDistance;
	glm::mat4 proj;
	glm::mat4 view;
	float x;
	float y;
	glm::vec3 ray_nds;
	glm::vec4 ray_clip;
	glm::vec4 rayEye;
	glm::vec3 rayWorld;
	glm::vec3 worldRay;
};


