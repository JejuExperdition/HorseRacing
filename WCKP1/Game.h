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

	void setNextLevel(GameLevel* nextLevel);
private:
	bool frame();

	GameLevel* m_CurLevel;
	GameLevel* m_NextLevel;
};