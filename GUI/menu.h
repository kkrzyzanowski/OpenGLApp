#pragma once

#ifndef MENU_API
#define MENU_API
#endif // !MENU_API

// forward declarations zamiast includowania OpenGLScene.h
namespace AppEngine { class OpenGLScene; }
struct GLFWwindow;

namespace MenuGUI
{
	MENU_API void ShowEditor(bool* p_open);
	MENU_API void ShowScene(bool* p_open, GLFWwindow* window);
	MENU_API void RenderSceneToGUI();
	MENU_API void ShowLeftMenu(bool* p_open);
	MENU_API void ShowRightMenu(bool* p_open);
	MENU_API void ShowBottomMenu(bool* p_open);
	MENU_API void SceneMenu(bool* p_open);
	MENU_API void CloseScene();

	MENU_API AppEngine::OpenGLScene* GetScene();
}
