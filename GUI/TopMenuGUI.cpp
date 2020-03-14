#include "imgui.h"
#include "menu.h"
void MenuGUI::ShowTopMenu(bool* p_open)
{
	ImGui::SetNextWindowPos(ImVec2(650, 20), ImGuiCond_FirstUseEver);
	ImGui::SetNextWindowSize(ImVec2(550, 680), ImGuiCond_FirstUseEver);
	
	ImGuiWindowFlags flags = 0;
	ImGuiID dockspaceId = 0;

	if (!ImGui::Begin("Top Menu", p_open, flags))
	{
		// Early out if the window is collapsed, as an optimization.
		ImGui::End();
		return;
	}
	ImGuiDockNodeFlags dockspaceFlags = ImGuiDockNodeFlags_None;
	ImGuiID dockspaceID = ImGui::GetID("nn");
	if (!ImGui::DockBuilderGetNode(dockspaceID)) {
		ImGui::DockBuilderRemoveNode(dockspaceID);
		ImGui::DockBuilderAddNode(dockspaceID, ImGuiDockNodeFlags_None);

		ImGuiID dock_main_id = dockspaceID;
		ImGuiID dock_up_id = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Up, 0.05f, nullptr, &dock_main_id);
		ImGuiID dock_right_id = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Right, 0.2f, nullptr, &dock_main_id);
		ImGuiID dock_left_id = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Left, 0.2f, nullptr, &dock_main_id);
		ImGuiID dock_down_id = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Down, 0.2f, nullptr, &dock_main_id);
		ImGuiID dock_down_right_id = ImGui::DockBuilderSplitNode(dock_down_id, ImGuiDir_Right, 0.6f, nullptr, &dock_down_id);

		ImGui::DockBuilderDockWindow("Actions", dock_up_id);
		ImGui::DockBuilderDockWindow("Hierarchy", dock_right_id);
		ImGui::DockBuilderDockWindow("Inspector", dock_left_id);
		ImGui::DockBuilderDockWindow("Console", dock_down_id);
		ImGui::DockBuilderDockWindow("Project", dock_down_right_id);
		ImGui::DockBuilderDockWindow("Scene", dock_main_id);

		// Disable tab bar for custom toolbar
		ImGuiDockNode* node = ImGui::DockBuilderGetNode(dock_up_id);
		node->LocalFlags |= ImGuiDockNodeFlags_NoTabBar;

		ImGui::DockBuilderFinish(dock_main_id);
	}
	ImGui::DockSpace(dockspaceID, ImVec2(0.0f, 0.0f), dockspaceFlags);
	ImGui::DockSpace(dockspaceId, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_None | ImGuiDockNodeFlags_PassthruCentralNode);
	ImGui::End();
	ImGui::SetNextWindowDockID(dockspaceId, ImGuiCond_FirstUseEver);

	if (ImGui::Begin("test2"))
	{
		ImGui::TextUnformatted("test2");
	}
	ImGui::Button("Insert Figures");
	ImGui::End();
}