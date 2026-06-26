#include "GUIWindow.h"

int main(int, char**)
{
	GUIWindow* gui = new GUIWindow();
	gui->RunGUIWindow(1280, 720);
	delete gui;
	return 0;
}