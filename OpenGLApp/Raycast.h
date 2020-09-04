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
	glm::vec3 GetWorldRayDirection();
	glm::vec3 GetRayOrigin();

	~Raycast();
private:
	unsigned int rayDistance;
	glm::mat4 proj;
	glm::mat4 view;
	float x;
	float y;
	float z;
	glm::vec3 ray_nds;
	glm::vec4 rayStartClip;
	glm::vec4 rayEndClip;
	glm::vec4 rayStartCamera;
	glm::vec4 rayStartWorld;
	glm::vec4 rayEndCamera;
	glm::vec4 rayEndWorld;
	glm::vec4 rayDirWorld;
	glm::vec3 origin;
	glm::vec3 worldRayNormalized;
};


