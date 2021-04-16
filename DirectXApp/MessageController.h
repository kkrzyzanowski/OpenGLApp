#pragma once
#include <Windows.h>
#include "KeyboardController.h"
#include "MouseController.h"
class MessageController
{
public:
	MessageController(HINSTANCE hInstance, const wchar_t* sClassName);
	void InitializeWindowProperty();
	LRESULT MessageHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	static LRESULT WINAPI HandleMessageSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	static LRESULT WINAPI HandleMessageInvoker(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
private:
	WNDCLASSEX wc;
	HINSTANCE hInstance;
	const wchar_t* sClassName;
	KeyboardController keyboard;
	MouseController mouse;
};

