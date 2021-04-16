#pragma once
#include <Windows.h>
#include "MessageController.h"

class DirectXWindow
{
public:
	DirectXWindow(HINSTANCE hInstance);
	int MakeWindow();
	int RunLoop();
	~DirectXWindow();
private:
	HWND hWindow;
	HINSTANCE hInstance;
	static constexpr const wchar_t* sClassName = L"DirectXApp";
	MessageController* msgController;
};

