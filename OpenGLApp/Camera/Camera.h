#pragma once
#include <vector>
#include "Raycast.h"
#include "..\glm\glm.hpp"
#include "..\glm\gtc\matrix_transform.hpp"
#include "..\glm\gtc\type_ptr.hpp"
#include "..\Buffers\UniformBuffer.h"
#include "..\Managers\ShapeManager.h"
#include "..\PointTranslator.h"
#include "..\DataStructures.h"
#include "..\Config.h"


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
	void scroll_callback(float xoffset, float yoffset);
	void MoveShapeWithCamera(Direction dir);
	void InitializeViewProjectionUniformBuffer();
	CameraState GetState() const;

	void SetActive();
	void SetInActive();


	inline glm::vec3 GetCamTarget() const { return camTarget; };
	inline void SetCamTarget(glm::vec3 camTarget) { this->camTarget = camTarget; };
	inline void SetMoving(bool m_isMoving) { this->isMoving = m_isMoving; };

	glm::mat4 GetView() const;
	glm::mat4 GetProjection() const;
	glm::vec3 GetCamPos() const;

	void PassProjectionToShaders();
	void PassViewToShaders();

	Raycast* mouseRayCast;
	UniformBuffer* ub;

	glm::vec3 camPos;
	glm::vec3 camTarget;
	glm::vec3 camDirection;
	glm::mat4 camView;


	std::vector<std::shared_ptr<Shape>> movableShapes;

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
