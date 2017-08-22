#include <Windows.h>
#include "Game.h"
HINSTANCE instanceHandle;
int show;

int WINAPI WinMain(HINSTANCE instanceHandle, HINSTANCE prevInstanceHandle, PSTR commandLine, int show)
{
	::instanceHandle = instanceHandle;
	::show = show;

	Game::initialize();

	Game::getInstance()->run();

	Game::shutdown();

	return 0;
}