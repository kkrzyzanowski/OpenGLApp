#include "Camera.h"
#include <math.h>

Camera* camInstance;
float lastX;
float lastY;
bool firstMouse;
float yaw;
float pitch; 
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
Camera::Camera()
{
	if(camInstance == NULL)
		camInstance = this;
	lastX = 1280 / 2;
	lastY = 720/2;
	firstMouse = true;
	pitch = 0.0f;
	yaw = -90.0f;
	camView = glm::mat4(1.0f);
}

void Camera::CreateView(glm::vec3(&vecArray)[3], float radius, GLFWwindow *window)
{
	camPos = vecArray[0];
	camTarget = vecArray[1];
	camDirection = vecArray[2];
	this->radius = radius;
	this->window = window;
	deltaTime = 0.0f;
	lastFrame = 0.0f;
	
	fov = 100.0f;
	camView = glm::lookAt(camPos, camPos + camTarget, camDirection);
	glfwSetCursorPosCallback(window, mouse_callback);
}

void Camera::Update()
{
	
	currentFrame = glfwGetTime();
	float camX = sin(glfwGetTime()) * radius;
	float camZ = cos(glfwGetTime()) * radius;
	//camPos = glm::vec3(camX, camPos.y, camZ);
	
	CameraMove(10.0f);
	camView = glm::lookAt(camPos, camPos + camTarget, camDirection);
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;
	
}

void Camera::CameraMove(float speed)
{
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camPos += speed * deltaTime * camTarget;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camPos -= speed * deltaTime * camTarget;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camPos -= glm::normalize(glm::cross(camDirection, camTarget)) * speed * deltaTime;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camPos +=  glm::normalize(glm::cross(camDirection, camTarget)) * speed * deltaTime;

}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
 if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}
	float xoffset = xpos - lastX;
	float yoffset = ypos - lastY;
	lastX = xpos;
	lastY = ypos;

	float sensivity = 0.05f;
	xoffset *= sensivity;
	yoffset *= sensivity;

	pitch += yoffset;
	yaw -= xoffset;

	if (pitch > 89.0f)
	pitch = 89.0f;
	if (pitch < -89.0f)
	pitch = -89.0f;
	glm::vec3 front;
	front.x =  cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	camInstance->SetCamTarget(glm::normalize(front));
}

void Camera::scroll_callback(double xoffset, double yoffset)
{
	if (fov >= 1 && fov <= 108.0f)
		fov -= yoffset;
	if (fov < 1.0f)
		fov = 1.0f;
	if (fov >= 45.0f)
		fov = 45.0f;
}

glm::mat4 Camera::GetView()
{
	return camView;
}

glm::vec3 Camera::GetCamPos()
{
	return camPos;
}

Camera::~Camera()
{

}
