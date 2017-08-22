#include "GameWindow.h"
#include "Input.h"
#include "Error.h"
extern HINSTANCE instanceHandle;
extern int show;

void GameWindow::processEvents()
{
	MSG msg = { 0 };

	while (PeekMessage(&msg, m_WindowHandle, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);

		if (msg.message == WM_QUIT)
		{
			m_ShouldClose = true;
		}
	}
}

HWND GameWindow::getWindowHandle() const
{
	return m_WindowHandle;
}

bool GameWindow::windowShouldClose() const
{
	return m_ShouldClose;
}

void GameWindow::createWindow(HINSTANCE instanceHandle, int show)
{
	bool result;

	WNDCLASS wc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.hCursor = LoadCursor(0, IDC_ARROW);
	wc.hIcon = LoadIcon(0, IDI_APPLICATION);
	wc.hInstance = instanceHandle;
	wc.lpfnWndProc = WndProc;
	wc.lpszClassName = L"Name";
	wc.lpszMenuName = L"Name";
	wc.style = CS_HREDRAW | CS_VREDRAW;

	result = RegisterClass(&wc);
	if (!result)
	{
		error("RegisterClass Error");
	}

	m_WindowHandle = CreateWindow(L"Name", L"Name", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
		1920, 1080, 0, 0, instanceHandle, 0);
	if (!m_WindowHandle)
	{
		error("CreateWindow Error");
	}

	ShowWindow(m_WindowHandle, show);
	UpdateWindow(m_WindowHandle);
}

GameWindow::GameWindow():
	m_ShouldClose(false)
{
	createWindow(::instanceHandle, ::show);
}

GameWindow::~GameWindow()
{
	//DestroyWindow(m_WindowHandle);
}

LRESULT CALLBACK WndProc(HWND windowHandle, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		exit(0);
		break;
	case WM_LBUTTONUP:
		Input::getInstance()->setMouseInput(0, false);
		break;
	case WM_LBUTTONDOWN:
		Input::getInstance()->setMouseInput(0, true);
		break;
	case WM_RBUTTONUP:
		Input::getInstance()->setMouseInput(1, false);
		break;
	case WM_RBUTTONDOWN:
		Input::getInstance()->setMouseInput(1, true);
		break;
	}
	return DefWindowProc(windowHandle, message, wParam, lParam);
}