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

	while (PeekMessageW(&msg, nullptr, 0, 0, PM_REMOVE))
	{
		if (msg.message == WM_QUIT)
		{
			return msg.wParam;
		}
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}

DirectXWindow::~DirectXWindow()
{
	
}
