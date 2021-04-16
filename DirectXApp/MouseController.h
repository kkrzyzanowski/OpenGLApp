#pragma once
#include <queue>
#include <bitset>

class MouseController
{
public:
	class Event
	{
	public:
		enum class Type
		{
			MousePressed,
			MouseReleased,
			WheelUp,
			WheelDown,
			Move,
			Invalid
		};
		enum MouseButton
		{
			LEFT, RIGHT, WHEEL
		};
	private:
		Type type;
		bool pressed;
	public:
		Event() : type(Type::Invalid), pressed(false) {}
		Event(Type type) : type(type) {}
		bool IsPressed() const { return type == Type::MousePressed; }
		bool IsReleased() const { return type == Type::MouseReleased; }
		unsigned char GetPressedState() const { return pressed; }
	};

	MouseController();
	Event ReadMoouseButton();
	bool MouseButtonIsPressed(unsigned char buttonCode);
	void OnMouseButtonPressed(int x, int y, Event::MouseButton mb);
	void OnMouseButtonReleased(int x, int y, Event::MouseButton mb);
	void OnMouseMove(int x, int y);
	std::pair<int,int> GetMousePos();
	void FlushButton();
	void Flush();
	void ClearState();
	void ChangeRepeating();
	bool IsRepeating();
	template<typename T>
	void TrimBuffer(std::queue<T>& buffer);
private:
	static constexpr unsigned int nKeys = 3u;
	std::bitset<nKeys> buttonStates;
	std::queue<Event> mouseButtonBuffer;
	bool repeatingMouseButton = false;
	std::pair<int, int> mousePos;

};

