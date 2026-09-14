#pragma once

#ifndef MENU_API
#define MENU_API
#endif 

#include <OpenGLScene.h>

namespace AppEngine
{
    class OpenGLScene;
}

namespace MenuGUI
{
    MENU_API void CreateAddWindow(bool* p_open, AppEngine::OpenGLScene* scene);
};

