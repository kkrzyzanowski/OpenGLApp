#pragma once

#ifndef MENU_API
#define MENU_API
#endif // !MENU_API

namespace MenuGUI
{
	MENU_API void ShowTopMenu(bool* p_open);
	MENU_API void ShowLeftMenu(bool* p_open);
	MENU_API void ShowRightMenu(bool* p_open);
	MENU_API void ShowBottomMenu(bool* p_open);
	MENU_API void SceneMenu(bool* p_open);
}
