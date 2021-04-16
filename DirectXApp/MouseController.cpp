#include "MouseController.h"

MouseController::MouseController()
{
}

MouseController::Event MouseController::ReadMoouseButton()
{
	if (mouseButtonBuffer.size() > 0u)
	{
		MouseController::Event e = mouseButtonBuffer.front();
		mouseButtonBuffer.pop();
		return e;
	}
	else
		return MouseController::Event();
}

bool MouseController::MouseButtonIsPressed(unsigned char buttonCode)
{
	return false;
}

void MouseController::OnMouseButtonPressed(int x , int y, MouseController::Event::MouseButton mb)
{
	buttonStates[mb] = true;
	mouseButtonBuffer.push(MouseController::Event(MouseController::Event::Type::MousePressed));
	TrimBuffer(mouseButtonBuffer);
}

void MouseController::OnMouseButtonReleased(int x, int y, MouseController::Event::MouseButton mb)
{
	buttonStates[mb] = false;
	mouseButtonBuffer.push(MouseController::Event(MouseController::Event::Type::MouseReleased));
	TrimBuffer(mouseButtonBuffer);
}

void MouseController::OnMouseMove(int x, int y)
{
	mousePos.first = x;
	mousePos.second = y;
	mouseButtonBuffer.push(MouseController::Event(MouseController::Event::Type::Move));
	TrimBuffer(mouseButtonBuffer);
}

std::pair<int, int> MouseController::GetMousePos()
{
	return mousePos;
}

void MouseController::FlushButton()
{
	mouseButtonBuffer = std::queue<Event>();
}

void MouseController::Flush()
{
	buttonStates.reset();
}

void MouseController::ClearState()
{
}

void MouseController::ChangeRepeating()
{
	repeatingMouseButton = !repeatingMouseButton;
}

bool MouseController::IsRepeating()
{
	return repeatingMouseButton;
}

template<typename T>
void MouseController::TrimBuffer(std::queue<T>& buffer)
{
	while (buffer.size() > nKeys)
	{
		buffer.pop();
	}
}
