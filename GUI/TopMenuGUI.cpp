#include "imgui.h"
#include "imgui_internal.h"
#include "menu.h"
#include <vector>
void MenuGUI::ShowTopMenu(bool* p_open)
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
	if (ImGui::Begin("testDock", p_open, flags))
	{

		ImGui::PopStyleVar(3);
	ImGuiIO io = ImGui::GetIO();
	ImGuiID dockspaceId = ImGui::GetID("test1");
	ImGuiContext* context = ImGui::GetCurrentContext();
	ImGuiDockNodeFlags nodeFlags =	NULL;
	ImGuiContext* ctx = ImGui::GetCurrentContext();
	ImGui::DockBuilderRemoveNode(dockspaceId);
	ImGui::DockBuilderAddNode(dockspaceId, nodeFlags);
	ImGui::DockBuilderSetNodeSize(dockspaceId, viewport->Size);
	ImGuiID dock_main_id = dockspaceId;
	ImGuiID dock_id_prop = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Left, .2f, NULL, &dock_main_id);
	ImGuiID dock_id_bottom = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Down, 1.0f, NULL, &dock_main_id);
	ImGuiID dock_id_gameWindow = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Right, 0.2f, NULL, &dock_main_id);


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

	ImVec2 leftPanelSize = ImVec2(viewport->Size.x * 0.2f, (viewport->Size.y - menuBarSize.y) * 1.01f);
	ImGuiWindowFlags tabBarflags =NULL;

	if(ImGui::BeginChild(dock_id_prop, leftPanelSize, true, tabBarflags))
	{
		propSize = ImGui::GetWindowSize();
		propPosition = ImGui::GetWindowPos();
		if (ImGui::BeginTabBar("blah"))
		{
			if (ImGui::BeginTabItem("Video"))
			{
				ImGui::Text("Blah blah");
				ImGui::EndTabItem();
			}
			if (ImGui::BeginTabItem("Audio"))
			{
				ImGui::EndTabItem();
			}
			if (ImGui::BeginTabItem("Controls"))
			{
				ImGui::EndTabItem();
			}
			ImGui::EndTabBar();
		}
	}
	ImGui::EndChild();

	ImVec2 downPanelSize = ImVec2((viewport->Size.x - leftPanelSize.x), (viewport->Size.y - menuBarSize.y) * 0.88f);
	ImGuiWindowFlags downBarflags = NULL;

	ImGui::SetNextWindowPos(ImVec2(leftPanelSize.x, propPosition.y));
	if (ImGui::BeginChild(dock_id_bottom, downPanelSize, true, downBarflags))
	{
		//ImGuiStyle& downBarStyle = ImGui::GetStyle();
		//downBarStyle.WindowPadding = ImVec2(15.0f, 15.0f);
		//downBarStyle.
		if (ImGui::BeginTabBar("blah"))
		{
			if (ImGui::BeginTabItem("gfdsg"))
			{
				ImGui::Text("gdfgfd");
				ImGui::EndTabItem();
			}
			if (ImGui::BeginTabItem("Audio"))
			{
				ImGui::EndTabItem();
			}
			if (ImGui::BeginTabItem("Controls"))
			{
				ImGui::EndTabItem();
			}
			ImGui::EndTabBar();
		}
	}
	ImGui::EndChild();

	ImVec2 windowPanelSize = ImVec2((viewport->Size.x - leftPanelSize.x) , (viewport->Size.y - menuBarSize.y));
	ImGuiWindowFlags windowBarFlags = NULL;
	ImGui::SetNextWindowPos(ImVec2(viewport->Size.x * 0.2f, viewport->Size.y* 0.91f));
	if (ImGui::BeginChild(dock_id_gameWindow, windowPanelSize, true, windowBarFlags))
	{
		if (ImGui::BeginTabBar("blah"))
		{
			if (ImGui::BeginTabItem("Video"))
			{
				ImGui::Text("Blagegd");
				ImGui::EndTabItem();
			}
			if (ImGui::BeginTabItem("Audio"))
			{
				ImGui::EndTabItem();
			}
			if (ImGui::BeginTabItem("Controls"))
			{
				ImGui::EndTabItem();
			}
			ImGui::EndTabBar();
		}
	}
	ImGui::EndChild();

	}
	
	ImGui::End();
}