#include "Input.h"

void Input::setMouseInput(int button, bool state)
{
	m_MouseState[button] = state;
}

bool Input::getKey(int key)
{
	return static_cast<bool>(GetAsyncKeyState(key) & 0x8000);
}

bool Input::getButton(int button)
{
	return m_MouseState[button];
}