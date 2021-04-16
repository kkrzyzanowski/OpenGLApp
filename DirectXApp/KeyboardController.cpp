
#include "KeyboardController.h"

KeyboardController::KeyboardController()
{
}

KeyboardController::Event KeyboardController::ReadKey()
{
    if (keybuffer.size() > 0u)
    {
        KeyboardController::Event e = keybuffer.front();
        keybuffer.pop();
        return e;
    }
    else
        return KeyboardController::Event();
}

bool KeyboardController::KeyIsPressed(unsigned char keycode)
{
    return keystates[keycode];
}

void KeyboardController::OnKeyPressed(unsigned char keycode)
{
    keystates[keycode] = true;
    keybuffer.push(KeyboardController::Event(KeyboardController::Event::Type::Pressed, keycode));
    TrimBuffer(keybuffer);

}

void KeyboardController::OnKeyReleased(unsigned char keycode)
{
    keystates[keycode] = false;
    keybuffer.push(KeyboardController::Event(KeyboardController::Event::Type::Released, keycode));
    TrimBuffer(keybuffer);
}

void KeyboardController::FlushKey()
{
    keybuffer = std::queue<Event>();
}

void KeyboardController::Flush()
{
}

void KeyboardController::ClearState()
{
    keystates.reset();
}

void KeyboardController::ChangeRepeating()
{
    repeatingKey = !repeatingKey;
}

bool KeyboardController::IsRepeating()
{
    return repeatingKey;
}

template<typename T>
void KeyboardController::TrimBuffer(std::queue<T>& buffer)
{
    while (buffer.size() > 0u)
    {
        buffer.pop();
    }
}
