#pragma once
#include <queue>
#include <bitset>

class KeyboardController
{
public:
	class Event
	{
	public:
		enum class Type
		{
			Pressed,
			Released,
			Invalid
		};
	private:
		Type type;
		unsigned char code;
	public:
		Event() : type(Type::Invalid), code(0u) {}
		Event(Type type, unsigned char code) : type(type), code(code) {}
		bool IsPressed() const { return type == Type::Pressed; }
		bool IsReleased() const { return type == Type::Released; }
		unsigned char GetCode() const { return code; }
	};

	KeyboardController();
	Event ReadKey();
	bool KeyIsPressed(unsigned char keycode);
	void OnKeyPressed(unsigned char keycode);
	void OnKeyReleased(unsigned char keycode);
	void FlushKey();
	void Flush();
	void ClearState();
	void ChangeRepeating();
	bool IsRepeating();
	template<typename T>
	void TrimBuffer(std::queue<T>& buffer);
private:
	static constexpr unsigned int nKeys = 256u;
	std::bitset<nKeys> keystates;
	std::queue<Event> keybuffer;
	bool repeatingKey = false;
};

