#include "ShapeManager.h"
#include <algorithm>
#include <math.h>
#include <iostream>
#include "Camera.h"
#include "Config.h"
#include "Plane.h"

Camera* camInstance;
CameraManager* CameraManager::camManager;
float lastX;
float lastY;
float speed = 10.0f;
bool firstMouse;
float yaw;
float pitch; 
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void mouseButtonCallback(GLFWwindow* window, int button, int action, int mode);
bool RayCastDetection(glm::vec3 rayOrigin, glm::vec3 rayDirection, glm::mat4 shapeModel, Triangles& triangles, float distance);
void ObjectPicking(int mx, int my, std::vector<std::shared_ptr<Shape>>& shapes);
Camera::Camera()
{
	if(camInstance == NULL)
		camInstance = this;
	lastX = SCREEN_WIDTH / 2;
	lastY = SCREEN_HEIGHT/2;
	firstMouse = true;
	pitch = 0.0f;
	yaw = -90.0f;
	camView = glm::mat4(1.0f);
	stateCam = CameraState::INACTIVE;
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
	fov = glm::radians(90.0f);

	projection = glm::perspective(fov, 16.0f / 9.0f, .01f, 1000.0f);
	camView = glm::lookAt(camPos, camPos + camTarget, camDirection);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetMouseButtonCallback(window, mouseButtonCallback);
}

void Camera::Update()
{
	
	currentFrame = glfwGetTime();
	//float camX = sin(glfwGetTime()) * radius;
	//float camZ = cos(glfwGetTime()) * radius;
	//camPos = glm::vec3(camX, camPos.y, camZ);
	
	CameraMove();
	camView = glm::lookAt(camPos, camPos + camTarget, camDirection);
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;
	
}

void Camera::CameraMove()
{
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camPos += speed * deltaTime * camTarget;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camPos -= speed * deltaTime * camTarget;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camPos -= glm::normalize(glm::cross(camTarget, camDirection)) * speed * deltaTime;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camPos +=  glm::normalize(glm::cross(camTarget, camDirection)) * speed * deltaTime;

}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{	

	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
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

		pitch -= yoffset;
		yaw += xoffset;

		if (pitch > 89.0f)
			pitch = 89.0f;
		if (pitch < -89.0f)
			pitch = -89.0f;
		glm::vec3 front;
		front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
		front.y = sin(glm::radians(pitch));
		front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
		camInstance->SetCamTarget(glm::normalize(front));
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_RELEASE)
	{
		firstMouse = true;
	}

	
}

void mouseButtonCallback(GLFWwindow* window, int button, int action, int mode)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT)
	{
		double mx, my;
		glfwGetCursorPos(window, &mx, &my);
		//RAYCAS failed to-do
		float distance = 1000.0f;
		camInstance->mouseRayCast = new Raycast(mx, my, distance, camInstance->GetProjection(), camInstance->GetView());


		for each (auto & shape in ShapeManager::shapes)
		{
			glm::vec3 startPoint = camInstance->mouseRayCast->GetRayOrigin();
			glm::vec3 startDir = camInstance->mouseRayCast->GetWorldRayDirection();
			glm::vec3 aabbMin = glm::vec3(-.5f, -.5f, -4.5f);
			glm::vec3 aabbMax = glm::vec3(.5f, .5f, -4.5f);
			bool detected = RayCastDetection(startPoint, startDir, shape->GetModel(), shape->GetTriangles(), 1000.0f);
			if (detected)
			{
				shape->Selected = true;
			}
			else
			{
				shape->Selected = false;
			}
		}
		//ObjectPicking(mx, my, ShapeManager::shapes);
		delete camInstance->mouseRayCast;
	}
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

void Camera::MoveShapeWithCamera(Direction dir)
{
	for (auto& shape : movableShapes)
	{
		shape->Translate(dir, speed*deltaTime);
	}
}

CameraState Camera::GetState()
{
	return stateCam;
}

void Camera::SetActive()
{
	stateCam = CameraState::ACTIVE;
}

void Camera::SetInActive()
{
	stateCam = CameraState::INACTIVE;
}

glm::mat4 Camera::GetView()
{
	return camView;
}

glm::mat4 Camera::GetProjection()
{
	return projection;
}

glm::vec3 Camera::GetCamPos()
{
	return camPos;
}

Camera::~Camera()
{

}

CameraManager::CameraManager()
{
	
	if (camManager == nullptr)
	{
		camManager = this;
	}
}
void CameraManager::AddCamera(Camera * cam)
{
	//cam.setId() itd jfdsajgk
	Cameras.push_back(cam);
}

void CameraManager::RemoveCamera(Camera * cam)
{
	std::vector<Camera*>::iterator it = std::find_if(Cameras.begin(), Cameras.end(), [&cam](const Camera* lcam) { return lcam == cam; });
	Cameras.erase(it);
}

void CameraManager::SetActiveCamera(Camera * cam)
{
	if (cam->GetState() != CameraState::ACTIVE)
		cam->SetActive();
	for each (Camera* cm in Cameras)
	{
		if (cm != cam)
		{
			cm->SetInActive();
		}
	}
}

Camera * CameraManager::GetActiveCamera()
{
	for each (Camera* cam in Cameras)
	{
		if (cam->GetState() == CameraState::ACTIVE)
			return cam;
	}
	return nullptr;
}

CameraManager * CameraManager::GetInstance()
{
	return camManager;
}

CameraManager::~CameraManager()
{
}


long ConvertToId(unsigned char* data)
{
	std::string id;
	for (unsigned char* ch = data; *ch; ++ch)
	{
		char buffer[4];
		sprintf(buffer, "%d", (int)*ch);
		id = id + buffer;
	}
	return std::stol(id);
}

void ObjectPicking(int mx, int my, std::vector<std::shared_ptr<Shape>>& shapes)
{
	unsigned char data[4];
	long colorId;
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glReadPixels(mx, my, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, &data);
		data[3] = '\0';
		colorId = ConvertToId(data);
		for each (auto& shape in shapes)
		{
			if (colorId == shape->Id)
				std::cout << "Selected Shape " << std::endl;
		}
}


bool RayCastDetection(glm::vec3 rayOrigin, glm::vec3 rayDirection, glm::mat4 shapeModel, Triangles& triangles, float distance)
{
	for each (Triangle triangle in triangles)
	{
		glm::vec3 v0 = triangle[0];
		glm::vec3 v1 = triangle[1];
		glm::vec3 v2 = triangle[2];

		glm::vec3 edge1, edge2;
		glm::vec3 h, s, q;

		edge1 = v1 - v0;
		edge2 = v2 - v0;

		h = glm::cross(rayDirection, edge2);
		float a = glm::dot(edge1, h);
		if (fabs(a) < 0.0001f)
			continue;

		float f = 1.0 / a;

		s = rayOrigin - v0;
		float u = f * glm::dot(s, h);
		if (u < 0.0f || u > 1.0f)
			continue;
		
		q = glm::cross(s, edge1);
		float v = f * glm::dot(rayDirection, q);
		if (v < 0.0f || v + u > 1.0f)
			continue;

		float t = f * glm::dot(edge2, q);

		if (t > 0.0001f)
		{
			glm::vec3 intersectedPoint = rayOrigin + rayDirection * t;
			std::cout << "Detected!!!" << std::endl;
			return true;
		}
	}
	return false;
}