#include "Game.h"
#include "GameWindow.h"
#include "Graphics.h"
#include "Input.h"
#include "TLevel.h"

Game::Game() :
	m_CurLevel(nullptr)
{
	GameWindow::initialize();
	Graphics::initialize();
	Input::initialize();
	m_CurLevel = new TLevel(Graphics::getInstance()->getDevice());
}

Game::~Game()
{
	Input::shutdown();
	Graphics::shutdown();
	GameWindow::shutdown();
}

void Game::run()
{
	while (frame());
}

bool Game::frame()
{
	GameWindow::getInstance()->processEvents();

	if (GameWindow::getInstance()->windowShouldClose())
	{
		return false;
	}

	m_CurLevel->update(1 / 60.0f);

	Graphics::getInstance()->drawLevel(m_CurLevel);

	return true;
}