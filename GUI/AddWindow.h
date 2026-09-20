#pragma once
#if defined(_WIN32)
#include <Windows.h>
#endif // defined(_WIN32)

#ifndef MENU_API
#define MENU_API
#endif 

#include <OpenGLScene.h>
using namespace AppEngine;

namespace MenuGUI
{
	MENU_API void CreateAddWindow(bool* p_open, AppEngine::OpenGLScene* scene, ShapeType type, const std::string& filePath);
#if defined(_WIN32)
	MENU_API std::filesystem::path ShowWindowsDialog(bool* p_open, AppEngine::OpenGLScene* scene, ShapeType type, bool* p_open_dialog);
#endif
};

