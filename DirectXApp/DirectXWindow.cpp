#include "DirectXWindow.h"


DirectXWindow::DirectXWindow(HINSTANCE hInstance)
{
	this->hInstance = hInstance;
	MakeWindow();
}

int DirectXWindow::MakeWindow()
{
	msgController = new MessageController(hInstance, L"DirectXApp");
	msgController->InitializeWindowProperty();
	HWND hWindow = CreateWindowEx(0, sClassName, L"DirectXApp",
		WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, 960, 540, 1280, 720, nullptr,
		nullptr, hInstance, this);
	ShowWindow(hWindow, SW_SHOW);
	RunLoop();
	return 0;
}

int DirectXWindow::RunLoop()
{
	MSG msg;
	BOOL gResult;
	while ((gResult = GetMessage(&msg, nullptr, 0, 0)) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}

DirectXWindow::~DirectXWindow()
{
	
}
