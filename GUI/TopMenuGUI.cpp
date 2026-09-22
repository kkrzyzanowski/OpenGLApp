#include "imgui.h"
#include "imgui_internal.h"
#include "menu.h"
#include "AddWindow.h"
#include "EventHandler.h"

#include "OpenGLScene.h" // include tutaj (cpp), bo potrzebujesz pe³nej definicji w implementacji
#include <GLFW/glfw3.h>  // jeœli u¿ywasz bezpoœrednio typów GLFW lub funkcji
#include <vector>
#include <filesystem>
#include <iostream>

bool openAddDialog = false;
bool openWindowsDialog = false;
bool openSceneWindow = false;
bool isSceneHovered = false;
ImVec2 sceneSize;
ImVec2 downPanelSize;
ImVec2 scenePosition;
OpenGLScene* scene = nullptr;
std::shared_ptr<FrameBuffer> sceneFrameBuffer = nullptr;
std::string filePath;
ShapeType type{};
void SetSceneSizeAndPosition(ImVec2 size);

void MenuGUI::ShowEditor(bool* p_open)
{
	
	ImGuiViewport* viewport = ImGui::GetMainViewport();
	ImGuiWindowFlags flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking |
		ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
		ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
	ImGui::SetNextWindowPos(viewport->Pos);
	ImGui::SetNextWindowSize(viewport->Size);
	ImGui::SetNextWindowViewport(viewport->ID);

	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

	EventHandler::GetInstance().subscribe(EventType::OPEN_SCENE, []() { SetSceneSizeAndPosition(downPanelSize); });
	if (ImGui::Begin("testDock", p_open, flags))
	{

		ImGui::PopStyleVar(3);
		ImGuiIO io = ImGui::GetIO();
		ImGuiID dockspaceId = ImGui::GetID("test1");
		ImGuiContext* context = ImGui::GetCurrentContext();
		ImGuiDockNodeFlags nodeFlags = NULL;
		ImGuiContext* ctx = ImGui::GetCurrentContext();
		ImGui::DockBuilderRemoveNode(dockspaceId);
		ImGui::DockBuilderAddNode(dockspaceId, nodeFlags);
		ImGui::DockBuilderSetNodeSize(dockspaceId, viewport->Size);
		ImGuiID dock_main_id = dockspaceId;
		ImGuiID dock_id_prop = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Left, .2f, NULL, &dock_main_id);
		ImGuiID dock_id_gameWindow = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Right, 0.2f, NULL, &dock_main_id);
		ImGuiID dock_id_bottom = ImGui::DockBuilderSplitNode(dock_id_gameWindow, ImGuiDir_Down, .1f, NULL, &dock_id_gameWindow);


		ImGui::DockBuilderDockWindow("Shapes", dock_id_prop);
		ImGui::DockBuilderDockWindow("log", dock_id_bottom);
		ImGui::DockBuilderFinish(dock_main_id);
		ImVec2 menuBarSize = ImVec2();
		ImVec2 propSize = ImVec2();

		ImVec2 propPosition = ImVec2();

		if (ImGui::BeginMenuBar())
		{
			menuBarSize = ImGui::GetItemRectSize();
			if (ImGui::BeginMenu("Menu"))
			{
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Examples"))
			{
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Tools"))
			{
				ImGui::EndMenu();
			}
			ImGui::EndMenuBar();
		}


		ImVec2 leftPanelSize = ImVec2(viewport->Size.x * 0.2f, 0);
		ImGuiWindowFlags tabBarflags = NULL;
		scenePosition.x = leftPanelSize.x;
		if (ImGui::BeginChild(dock_id_prop, leftPanelSize, true, tabBarflags))
		{
			propSize = ImGui::GetWindowSize();
			propPosition = ImGui::GetWindowPos();

			if (ImGui::BeginTabBar("blah"))
			{
				if (ImGui::BeginTabItem("Shapes"))
				{
					if (ImGui::Button("Cube"))
					{
						openAddDialog = true;
						type = ShapeType::CUBE;
					}
					if (ImGui::Button("Plane"))
					{
						type = ShapeType::PLANE;
						openAddDialog = true;
					}
					if (ImGui::Button("Sphere"))
					{
						type = ShapeType::SPEHERE;
						openAddDialog = true;
					}
					if (ImGui::Button("Custom"))
					{
						//TO-DO implement window with path to object
						type = ShapeType::CUSTOM;
						openWindowsDialog = true;
					}
					if (openAddDialog)
					{
						MenuGUI::CreateAddWindow(&openAddDialog, scene, type, filePath);
					}
					else if (openWindowsDialog)
					{
						filePath = MenuGUI::ShowWindowsDialog(&openWindowsDialog, scene, type, &openAddDialog).string();
					}
					ImGui::EndTabItem();
				}

				ImGui::EndTabBar();
			}
		}
		ImGui::EndChild();

		ImVec2 availSize = ImGui::GetContentRegionAvail();
		float sceneHeightScene = 0.85f * propSize.y;
		float sceneHeightConsole = 0.10f * availSize.y;
		downPanelSize = ImVec2((viewport->Size.x - leftPanelSize.x), sceneHeightScene);
		ImVec2 consolePanelSize = ImVec2((viewport->Size.x - leftPanelSize.x), sceneHeightConsole);
		ImGuiWindowFlags downBarflags = ImGuiWindowFlags_NoBackground;
		float endPosSceneBarY = propPosition.y + sceneHeightScene;
		scenePosition.y = propPosition.y;
		ImGui::SetNextWindowPos(ImVec2(leftPanelSize.x, propPosition.y));
		if (ImGui::BeginChild(dock_id_gameWindow, downPanelSize, true, downBarflags))
		{
			if (ImGui::BeginTabBar("SceneTabBar"))
			{
				if (ImGui::BeginTabItem("Scene", p_open))
				{
					sceneSize = ImGui::GetContentRegionAvail();
					if (openSceneWindow)
					{
						ImGui::Image((void*)(intptr_t)sceneFrameBuffer->GetFramebufferTexture()->GetTextureID(), { sceneSize.x, sceneSize.y }, ImVec2(0,1), ImVec2(1, 0));
						isSceneHovered = ImGui::IsItemHovered();
					}
					else
					{
						ImGui::Text("Scene is not open");
					}
					if(ImGui::Button("Play"))
					{
						EventHandler::GetInstance().HandleEvent(EventType::OPEN_SCENE);
						
						// do something
						
					}
					if(ImGui::Button("Pause"))
					{
						// do something
					}
					if(ImGui::Button("Stop"))
					{
						EventHandler::GetInstance().HandleEvent(EventType::CLOSE_SCENE);

					}
					ImGui::EndTabItem();
				}
				ImGui::EndTabBar();
			}
		}
		ImGui::EndChild();

		ImGui::SetNextWindowPos(ImVec2(leftPanelSize.x, endPosSceneBarY));
		if (ImGui::BeginChild(dock_id_bottom, consolePanelSize, false, downBarflags))
		{
			if (ImGui::BeginTabBar("ConsoleTabBar"))
			{
				ImGui::BeginTabItem("Console");
				{
					// render console messages tutaj
					ImGui::TextWrapped("Console output...");
				}
				ImGui::EndTabItem();
			}
			ImGui::EndTabBar();
		}

		ImGui::EndChild();
	}

	ImGui::End();
}

void MenuGUI::ShowScene(bool* p_open, GLFWwindow* window)
{
	if (!openSceneWindow)
	{
		scene = new OpenGLScene(window, sceneSize, scenePosition);

		openSceneWindow = true;

	}
	scene->SetSceneHovered(isSceneHovered);
	sceneFrameBuffer = scene->RenderScene(sceneSize, scenePosition);

}

void MenuGUI::CloseScene()
{
	openSceneWindow = false;
	scene->ClearScene();
	delete scene;
	scene = nullptr;
}

OpenGLScene* MenuGUI::GetScene()
{
	return scene;
}


void SetSceneSizeAndPosition(ImVec2 size)
{
	sceneSize = size;
}
