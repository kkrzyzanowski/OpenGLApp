#pragma once
#include <vector>
#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtc\type_ptr.hpp"
#include <GLFW/glfw3.h>



enum View
{
	TPP, FPP
};
class Camera
{
public:
	Camera();
	void CreateView(glm::vec3(&vecArray)[3], float radius, GLFWwindow* window);
	void Update();
	void MouseMove(float movementSpeed);
	void CameraMove(float speed);
	void scroll_callback(double xoffset, double yoffset);
	
	inline glm::vec3 GetCamTarget() { return camTarget; };
	inline void SetCamTarget(glm::vec3 camTarget) { this->camTarget = camTarget; };
    glm::mat4 GetView();
	glm::vec3 GetCamPos();
	~Camera();
private:
	glm::vec3 camPos;
	glm::vec3 camTarget;
	glm::vec3 camDirection;
	GLFWwindow* window;
	glm::mat4 camView;
	float radius;
	float deltaTime;
	float lastFrame;
	float currentFrame;
	float fov;
};

