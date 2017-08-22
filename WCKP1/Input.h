#pragma once
#include "Singleton.h"
#include <Windows.h>

class Input : public Singleton<Input>
{
public:
	void setMouseInput(int button, bool state);

	bool getKey(int key);

	bool getButton(int button);
private:
	bool m_MouseState[2];
};