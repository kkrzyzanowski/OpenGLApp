#include "MessageController.h"

LRESULT  MessageController::MessageHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
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

LRESULT WINAPI MessageController::HandleMessageSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (msg == WM_NCCREATE)
	{
		const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(lParam);
		MessageController* const pWnd = static_cast<MessageController*>(pCreate->lpCreateParams); // Shoulde be DirectXwindow pointer

		SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWnd));
		SetWindowLongPtr(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&MessageController::HandleMessageInvoker));

		return pWnd->MessageHandler(hWnd, msg, wParam, lParam);
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

LRESULT WINAPI MessageController::HandleMessageInvoker(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	MessageController* const pMsg = reinterpret_cast<MessageController*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
	return pMsg->MessageHandler(hWnd, msg, wParam, lParam);
}

MessageController::MessageController(HINSTANCE hInstance, const wchar_t* sClassName)
{
	this->hInstance = hInstance;
	this->sClassName = sClassName;
	this->wc = { 0 };
}

void MessageController::InitializeWindowProperty()
{
	wc.cbSize = sizeof(wc);
	wc.style = CS_OWNDC;
	wc.lpfnWndProc = HandleMessageSetup;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = nullptr;
	wc.hCursor = nullptr;
	wc.hbrBackground = nullptr;
	wc.lpszMenuName = nullptr;
	wc.lpszClassName = (LPCWSTR)sClassName;
	wc.hIconSm = nullptr;
	RegisterClassEx(&wc);
}
