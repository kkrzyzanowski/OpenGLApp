#include <Windows.h>

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CLOSE:

		PostQuitMessage(69);
		break;
	case WM_KEYDOWN:
		if (wParam == 'W')
		{
			//do something
		}
		break;
	case WM_KEYUP:
		break;
	
	case WM_LBUTTONDOWN:
	
		POINTS point = MAKEPOINTS(lParam);
		break;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

int CALLBACK WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	const auto sClassName = L"DirectXApp";
	WNDCLASSEX wc = { 0 };
	wc.cbSize = sizeof(wc);
	wc.style = CS_OWNDC;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = nullptr;
	wc.hCursor = nullptr;
	wc.hbrBackground = nullptr;
	wc.lpszMenuName = nullptr;
	wc.lpszClassName = sClassName;
	wc.hIconSm = nullptr;
	RegisterClassEx(&wc);
	HWND hWindow = CreateWindowEx(0, sClassName, L"DirectXApp",
		WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, 960, 540, 1280, 720, nullptr,
		nullptr, hInstance, nullptr);
	ShowWindow(hWindow, SW_SHOW);
	MSG msg;
	BOOL gResult;
	while ((gResult = GetMessage(&msg, nullptr, 0, 0)) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	if (gResult == -1)
	{
		return -1;
	}
	else
		return 0;
}