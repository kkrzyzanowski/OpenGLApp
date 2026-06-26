#pragma once
#include <OpenGLScene.h>
#ifndef MENU_API
#define MENU_API
#endif // !MENU_API
using namespace AppEngine;
namespace MenuGUI
{
	MENU_API void ShowTopMenu(bool* p_open);
	MENU_API void ShowScene(bool* p_open, OpenGLScene*& scene, GLFWwindow* window);
	MENU_API void ShowLeftMenu(bool* p_open);
	MENU_API void ShowRightMenu(bool* p_open);
	MENU_API void ShowBottomMenu(bool* p_open);
	MENU_API void SceneMenu(bool* p_open);
}
