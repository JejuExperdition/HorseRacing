#pragma once
#include "Singleton.h"
#include "GameLevel.h"
#include <Windows.h>

const class Game : public Singleton<Game>
{
public:
	Game();
	Game(Game&) = delete;
	~Game();

	void run();
private:
	bool frame();

	GameLevel* m_CurLevel;
};