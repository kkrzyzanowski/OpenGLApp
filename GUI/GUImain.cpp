#include "GUIWindow.h"

int main(int, char**)
{
	GUIWindow* gui = new GUIWindow();
	gui->RunGUIWindow(1280, 720);
	return 0;
}