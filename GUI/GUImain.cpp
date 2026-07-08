#include "GUIWindow.h"

int main(int, char**)
{
	GUIWindow* gui = new GUIWindow();
	gui->RunGUIWindow(SCREEN_WIDTH, SCREEN_HEIGHT);
	delete gui;
	return 0;
}