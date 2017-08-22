#pragma once
#include "Singleton.h"
#include <Windows.h>

const class GameWindow : public Singleton<GameWindow>
{
public:
	GameWindow();
	GameWindow(GameWindow&) = delete;
	~GameWindow();

	void createWindow(HINSTANCE instanceHandle, int show);
	void processEvents();
	HWND getWindowHandle() const;
	bool windowShouldClose() const;
private:
	HWND m_WindowHandle;
	bool m_ShouldClose;
};

LRESULT CALLBACK WndProc(HWND instanceHandle, UINT message, WPARAM wParam, LPARAM lParam);