#include <algorithm>
#include <math.h>
#include <iostream>
#include "Camera.h"
#include "../../ImGUI/imgui_impl_glfw.h"
#include "../Managers/ShapeManager.h"

namespace AppEngine
{
	static Camera* camInstance;
	static GLFWcursorposfun prevCursorPosCallback = nullptr;
	static GLFWmousebuttonfun prevMouseButtonCallback = nullptr;
	CameraManager* CameraManager::camManager;
	float lastX;
	float lastY;
	float speed = 10.0f;
	bool firstMouse;
	float yaw;
	float pitch;
	glm::vec2 windowSize;
	glm::vec2 sceneSize;
	glm::vec2 windowPos;
	glm::vec2 previousPos;
	glm::vec2 deltaPos;
	glm::vec3 unprojectedPreviousPos;
	glm::vec3 previousModelPos;
	glm::vec3 previousDirection;
	glm::vec3 storedIntersectedPoint;
	glm::vec3 storedObjectPosition;

	bool lbuttonDown;
	double mx, my;

	void mouse_callback(GLFWwindow* window, double xpos, double ypos);
	void mouseButtonCallback(GLFWwindow* window, int button, int action, int mode);
	void hover_callback(GLFWwindow* window, double xpos, double ypos);

	bool RayCastDetection(glm::vec3 rayOrigin, glm::vec3 rayDirection, const Triangles& triangles, glm::vec3& intersectedPoint);
	void ObjectPicking(int mx, int my, std::vector<std::shared_ptr<Shape>>& shapes);
	glm::vec3 GetIntersection(glm::vec3 rayOrigin, glm::vec3 rayDirection, glm::vec3 planeNormal, glm::vec3 planePoint);

	Camera::Camera(glm::vec2 size, glm::vec2 scene, glm::vec2 pos)
	{
		if (camInstance == NULL)
			camInstance = this;
		windowSize = size;
		sceneSize = scene;
		windowPos = pos;
		lastX = size.x / 2.0f;
		lastY = size.y / 2.0f;
		firstMouse = true;
		pitch = 0.0f;
		yaw = -90.0f;
		camView = glm::mat4(1.0f);
		lbuttonDown = false;
		stateCam = CameraState::INACTIVE;
	}

	void Camera::CreateView(glm::vec3(&vecArray)[3], float radius, GLFWwindow* window)
	{
		camPos = vecArray[0];
		camTarget = vecArray[1];
		camDirection = vecArray[2];

		this->radius = radius;
		this->window = window;

		deltaTime = 0.0f;
		lastFrame = 0.0f;
		fov = glm::radians(90.0f); //field of view

		projection = glm::perspective(fov, 16.0f / 9.0f, 0.01f, 1000.0f); //projection create
		camView = glm::lookAt(camPos, camPos + camTarget, camDirection);

		prevCursorPosCallback = glfwSetCursorPosCallback(window, mouse_callback);
		prevMouseButtonCallback = glfwSetMouseButtonCallback(window, mouseButtonCallback);

	}

	void Camera::Update()
	{

		currentFrame = glfwGetTime();
		//float camX = sin(glfwGetTime()) * radius;
		//float camZ = cos(glfwGetTime()) * radius;
		//camPos = glm::vec3(camX, camPos.y, camZ);

		CameraMove();
		camView = glm::lookAt(camPos, camPos + camTarget, camDirection);
		PassViewToShaders();
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
			camPos += glm::normalize(glm::cross(camTarget, camDirection)) * speed * deltaTime;

	}

	void mouse_callback(GLFWwindow* window, double xpos, double ypos)
	{

		if (prevCursorPosCallback)
			prevCursorPosCallback(window, xpos, ypos);

		if (camInstance->GetSceneHovered())
		{
			mx = xpos;
			my = ypos;
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

				glm::vec3 front{};

				front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
				front.y = sin(glm::radians(pitch));
				front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
				camInstance->SetCamTarget(glm::normalize(front));
			}
			if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_RELEASE)
			{
				firstMouse = true;
			}
			if (lbuttonDown)
			{
				glm::mat4 proj, view;


				proj = camInstance->GetProjection();
				view = camInstance->GetView();

				PointTranslator mp;
				mp.proj = proj;
				mp.view = view;
				float x = (mx * 2.0f) / windowSize.x - 1.0f;
				mp.SetMousePoint(mx, my);
				mp.CalculateScaledMousePoint();

				for (auto& shape : ShapeManager::shapes)
				{
					if (shape->Selected)
					{
						camInstance->mouseRayCast = new Raycast(mx, my, 1000.0f, camInstance->GetProjection(), camInstance->GetView(), windowSize);
						glm::vec3 startPoint = camInstance->mouseRayCast->GetRayOrigin();
						glm::vec3 startDir = camInstance->mouseRayCast->GetWorldRayDirection();
						glm::vec3 intersectedDragPoint;

						if (RayCastDetection(startPoint, startDir, shape->GetTriangles(), intersectedDragPoint))
						{
							glm::vec3 offset = intersectedDragPoint - storedIntersectedPoint;
							shape->SetPendingOffset(offset);
							storedIntersectedPoint = intersectedDragPoint;
						}
					}
				}
			}
			previousPos.x = mx;
			previousPos.y = my;
		}
	}

	void mouseButtonCallback(GLFWwindow* window, int button, int action, int mode)
	{
		if (prevMouseButtonCallback)
			prevMouseButtonCallback(window, button, action, mode);

		glfwGetCursorPos(window, &mx, &my);
		if (button == GLFW_MOUSE_BUTTON_LEFT)
		{
			//RAYCAS failed to-do
			float distance = 1000.0f;
			float x = ((mx - windowPos.x) / sceneSize.x) * windowSize.x;
			float y = ((my - windowPos.y) / sceneSize.y) * windowSize.y;
			camInstance->mouseRayCast = new Raycast(x, y, distance, camInstance->GetProjection(), camInstance->GetView(), windowSize);

			for (auto& shape : ShapeManager::shapes)
			{
				glm::vec3 startPoint = camInstance->mouseRayCast->GetRayOrigin();
				glm::vec3 startDir = camInstance->mouseRayCast->GetWorldRayDirection();
				bool detected = RayCastDetection(startPoint, startDir, shape->GetTriangles(), storedIntersectedPoint);
				if (detected)
				{
					std::cout << "Clicked" << std::endl;
					shape->Selected = true;
				}
				else
				{
					shape->Selected = false;
				}
			}
			if (action == GLFW_PRESS)
			{
				lbuttonDown = true;
			}
			else if (action == GLFW_RELEASE)
			{
				lbuttonDown = false;
			}
			previousPos.x = (float)mx;
			previousPos.y = (float)my;
			delete camInstance->mouseRayCast;

		}
	}

	void Camera::scroll_callback(float xoffset, float yoffset)
	{
		if (fov >= 1.0f && fov <= 108.0f)
			fov -= yoffset;
		if (fov < 1.0f)
			fov = 1.0f;
		if (fov >= 45.0f)
			fov = 45.0f;
	}

	void Camera::MoveShapeWithCamera(Direction dir)
	{
		/*for (auto& shape : movableShapes)
		{
			shape->Translate(dir, speed*deltaTime);
		}*/
	}

	void Camera::InitializeViewProjectionUniformBuffer()
	{
		ub = new UniformBuffer(2 * sizeof(glm::mat4));
	}

	CameraState Camera::GetState() const
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

	glm::mat4 Camera::GetView() const
	{
		return camView;
	}

	glm::mat4 Camera::GetProjection() const
	{
		return projection;
	}

	glm::vec3 Camera::GetCamPos() const
	{
		return camPos;
	}

	void Camera::PassProjectionToShaders()
	{
		ub->Bind();
		ub->LoadData(glm::value_ptr(projection), sizeof(glm::mat4), 0);
		ub->UnBind();
	}

	void Camera::PassViewToShaders()
	{
		ub->Bind();
		ub->LoadData(glm::value_ptr(camView), sizeof(glm::mat4), sizeof(glm::mat4));
		ub->UnBind();
	}

	Camera::~Camera()
	{
		prevCursorPosCallback = nullptr;
		prevMouseButtonCallback = nullptr;
	}

	CameraManager::CameraManager()
	{

	}
	void CameraManager::AddCamera(Camera* cam)
	{
		//cam.setId() itd jfdsajgk
		Cameras.push_back(cam);
	}

	void CameraManager::RemoveCamera(Camera* cam)
	{
		std::vector<Camera*>::iterator it = std::find_if(Cameras.begin(), Cameras.end(), [&cam](const Camera* lcam) { return lcam == cam; });
		Cameras.erase(it);
	}

	void CameraManager::SetActiveCamera(Camera* cam)
	{
		if (cam->GetState() != CameraState::ACTIVE)
			cam->SetActive();
		for (Camera* cm : Cameras)
		{
			if (cm != cam)
			{
				cm->SetInActive();
			}
		}
	}

	Camera* CameraManager::GetActiveCamera()
	{
		for (Camera* cam : Cameras)
		{
			if (cam->GetState() == CameraState::ACTIVE)
				return cam;
		}
		return nullptr;
	}

	CameraManager* CameraManager::GetInstance()
	{
		if (camManager == nullptr)
		{
			camManager = new CameraManager();
		}
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
		for (auto& shape : shapes)
		{
			if (colorId == shape->Id)
				std::cout << "Selected Shape " << std::endl;
		}
	}
	/// <summary>
	/// Ray detection using Moller-Trumbore algorithm, returns true if ray intersects with triangle and false if not, also returns intersected point in case of intersection
	/// </summary>
	/// <param name="rayOrigin"></param>
	/// <param name="rayDirection"></param>
	/// <param name="triangles"></param>
	/// <param name="intersectedPoint"></param>
	/// <returns></returns>

	bool RayCastDetection(glm::vec3 rayOrigin, glm::vec3 rayDirection, const Triangles& triangles, glm::vec3& intersectedPoint)
	{
		for (Triangle triangle : triangles)
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

			float f = 1.0f / a;

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
				intersectedPoint = rayOrigin + rayDirection * t;
				std::cout << "Detected!!!" << std::endl;
				return true;
			}
		}
		return false;
	}

	glm::vec3 GetIntersection(glm::vec3 rayOrigin, glm::vec3 rayDirection, glm::vec3 planeNormal, glm::vec3 planePoint)
	{
		float dotProd = glm::dot(planeNormal, planePoint);
		float t = (dotProd - glm::dot(planeNormal, rayOrigin) / glm::dot(planeNormal, rayDirection));
		return rayOrigin + t * rayDirection;
	}
}