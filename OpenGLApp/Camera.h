#pragma once
#include <vector>
#include <GLFW/glfw3.h>
#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtc\type_ptr.hpp"
#include "Shape.h"
#include "Raycast.h"


enum View
{
	TPP, FPP
};

enum CameraState
{
	INACTIVE, ACTIVE, IN_USE
};
class Camera
{
public:
	Camera();
	void CreateView(glm::vec3(&vecArray)[3], float radius, GLFWwindow* window);
	void Update();
	void MouseMove(float movementSpeed);
	void CameraMove();
	void scroll_callback(double xoffset, double yoffset);
	void MoveShapeWithCamera(Direction dir);
	CameraState GetState();

	void SetActive();
	void SetInActive();
	

	inline glm::vec3 GetCamTarget() { return camTarget; };
	inline void SetCamTarget(glm::vec3 camTarget) { this->camTarget = camTarget; };
	inline void SetMoving(bool m_isMoving) { this->isMoving = m_isMoving; };

    glm::mat4 GetView();
	glm::mat4 GetProjection();
	glm::vec3 GetCamPos();
	
	Raycast* mouseRayCast;

	glm::vec3 camPos;
	glm::vec3 camTarget;
	glm::vec3 camDirection;
	glm::mat4 camView;


	std::vector<Shape*> movableShapes;
	
	~Camera();
private:

	GLFWwindow* window;
	glm::mat4 projection;
	CameraState stateCam;

	float radius;
	float deltaTime;
	float lastFrame;
	float currentFrame;
	float fov;
	bool isMoving;
};
 class CameraManager
{
public:
	CameraManager(); 
	static CameraManager* camManager;
	 void AddCamera(Camera* cam);
	 void RemoveCamera(Camera* cam);
	 void SetActiveCamera(Camera* cam);
	 Camera* GetActiveCamera();
	static CameraManager* GetInstance();
	 unsigned int cameraCount;
	 std::vector<Camera*> Cameras;
	~CameraManager();
};
