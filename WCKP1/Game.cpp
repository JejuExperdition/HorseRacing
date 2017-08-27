#include "Game.h"
#include "GameWindow.h"
#include "Graphics.h"
#include "Input.h"
#include "TLevel.h"

Game::Game() :
	m_CurLevel(nullptr),
	m_NextLevel(nullptr)
{
	GameWindow::initialize();
	Graphics::initialize();
	Input::initialize();
	TextureManager::initialize();
	m_CurLevel = new TLevel(Graphics::getInstance()->getDevice());
}

Game::~Game()
{
	TextureManager::shutdown();
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

	m_CurLevel->updateAll(1 / 60.0f);

	Graphics::getInstance()->drawLevel(m_CurLevel);

	if (m_NextLevel)
	{
		m_CurLevel = m_NextLevel;
		m_NextLevel = nullptr;
	}

	return true;
}

void Game::setNextLevel(GameLevel* nextLevel)
{
	m_NextLevel = nextLevel;
}