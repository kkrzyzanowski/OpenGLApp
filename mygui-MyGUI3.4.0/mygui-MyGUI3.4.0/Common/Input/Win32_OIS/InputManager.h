/*!
	@file
	@author		Albert Semenov
	@date		09/2009
	@module
*/

#ifndef INPUT_MANAGER_H_
#define INPUT_MANAGER_H_

#include <MyGUI.h>
#include <windows.h>
#include <OIS.h>

namespace input
{

	class InputManager :
		public OIS::KeyListener
	{
	public:
		InputManager();
		virtual ~InputManager();

		void createInput(size_t _handle);
		void destroyInput();
		void captureInput();
		void setInputViewSize(int _width, int _height);

		virtual void injectMouseMove(int _absx, int _absy, int _absz) { }
		virtual void injectMousePress(int _absx, int _absy, MyGUI::MouseButton _id) { }
		virtual void injectMouseRelease(int _absx, int _absy, MyGUI::MouseButton _id) { }
		virtual void injectKeyPress(MyGUI::KeyCode _key, MyGUI::Char _text) { }
		virtual void injectKeyRelease(MyGUI::KeyCode _key) { }

		virtual void onFileDrop(const std::wstring& _filename) { }
		virtual bool onWindowClose(size_t _handle) { return true; }

		void setMousePosition(int _x, int _y);
		void updateCursorPosition();

	private:
		static LRESULT CALLBACK windowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

		virtual bool keyPressed(const OIS::KeyEvent& _arg);
		virtual bool keyReleased(const OIS::KeyEvent& _arg);

		void frameEvent(float _time);
		void computeMouseMove();

		void mouseMove(int _absx, int _absy, int _absz);
		void mousePress(int _absx, int _absy, MyGUI::MouseButton _id);
		void mouseRelease(int _absx, int _absy, MyGUI::MouseButton _id);

	private:
		static InputManager* msInputManager;
		HWND mHwnd;
		static LRESULT msOldWindowProc;
		int mWidth;
		int mHeight;
		static bool msSkipMove;
		int mMouseX;
		int mMouseY;
		int mMouseZ;
		bool mMouseMove;

		OIS::InputManager* mInputManager;
		OIS::Keyboard* mKeyboard;
	};

} // namespace input

#endif // INPUT_MANAGER_H_
