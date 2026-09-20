#include "AddWindow.h"
#include <imgui.h>
#include <Managers/ShapeManager.h>
using namespace AppEngine;

void MenuGUI::CreateAddWindow(bool* p_open, OpenGLScene* scene, ShapeType type, const std::string& filePath)
{
    static bool no_titlebar = false;
    static bool no_scrollbar = false;
    static bool no_menu = false;
    static bool no_move = false;
    static bool no_resize = false;
    static bool no_collapse = false;
    static bool no_close = false;
    static bool no_nav = false;
    static bool no_background = false;
    static bool no_bring_to_front = false;
    static bool no_docking = false;
    static bool unsaved_document = false;
    ImGuiWindowFlags window_flags = 0;
    if (no_titlebar)        window_flags |= ImGuiWindowFlags_NoTitleBar;
    if (no_scrollbar)       window_flags |= ImGuiWindowFlags_NoScrollbar;
    if (!no_menu)           window_flags |= ImGuiWindowFlags_MenuBar;
    if (no_move)            window_flags |= ImGuiWindowFlags_NoMove;
    if (no_resize)          window_flags |= ImGuiWindowFlags_NoResize;
    if (no_collapse)        window_flags |= ImGuiWindowFlags_NoCollapse;
    if (no_nav)             window_flags |= ImGuiWindowFlags_NoNav;
    if (no_background)      window_flags |= ImGuiWindowFlags_NoBackground;
    if (no_bring_to_front)  window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus;
    if (no_docking)         window_flags |= ImGuiWindowFlags_NoDocking;
    if (unsaved_document)   window_flags |= ImGuiWindowFlags_UnsavedDocument;
    if (no_close)           p_open = NULL; // Don't pass our bool* to Begin

    const ImGuiViewport* main_viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(ImVec2(main_viewport->WorkPos.x + 650, main_viewport->WorkPos.y + 20), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(ImVec2(550, 680), ImGuiCond_FirstUseEver);

    if (!ImGui::Begin("Dear ImGui Demo", p_open, window_flags))
    {
        // Early out if the window is collapsed, as an optimization.
       
        ImGui::End();
        return;
    }

    static float color[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
    static float position[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
    static float rotation[3] = { 0.0f, 0.0f, 0.0f };
    static float scale[3] = { 1.0f, 1.0f, 1.0f};
    ImGui::DragFloat4("Position", position, 0.005f);
    ImGui::ColorEdit4("Color", color);
    ImGui::DragFloat3("Rotation", rotation, 0.005f);
    ImGui::DragFloat3("Scale", scale, 0.005f);
    if (ImGui::Button("Save"))
    {
        ///to-do make singleton of shapemanager
        auto shape = ShapeManager::AddShape(type, position, color, rotation, scale, filePath);
		scene->ReinitializeScene(shape);
        *p_open = false;
        ImGui::End();
        return;
    }
    if (ImGui::Button("Cancel"))
    {
        *p_open = false;
        ImGui::End();
        return;
    }
    ImGui::End();
}

std::filesystem::path MenuGUI::ShowWindowsDialog(bool* p_open, AppEngine::OpenGLScene* scene, ShapeType type, bool* p_open_dialog)
{
    OPENFILENAME ofn;       // common dialog box structure
    TCHAR szFile[260] = { 0 };       // if using TCHAR macros
	HWND hWnd = GetActiveWindow(); // Get the handle of the active window

    // Initialize OPENFILENAME
    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = hWnd; // Set the owner window handle
    ofn.lpstrFile = szFile;
    ofn.nMaxFile = sizeof(szFile);
    ofn.lpstrFilter = "Object files (*.obj)\0*.obj;\0";
    ofn.nFilterIndex = 1;
    ofn.lpstrFileTitle = NULL;
    ofn.nMaxFileTitle = 0;
    ofn.lpstrInitialDir = NULL;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;
    static float color[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
    static float position[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
    static float rotation[3] = { 0.0f, 0.0f, 0.0f };
    static float scale[3] = { 1.0f, 1.0f, 1.0f };

    if (GetOpenFileName(&ofn) == TRUE)
    {
        *p_open = false;
        *p_open_dialog = true;
		return ofn.lpstrFile;
    }
    else
    {
		*p_open = false;
        *p_open_dialog = false;
		return std::filesystem::path();
    }
}

