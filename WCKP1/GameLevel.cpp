#include "GameLevel.h"

GameLevel::GameLevel(ID3D11Device* device, const char* bgTexturePath):
	m_Camera(device),
	m_Background(device, &m_BGSprite),
	m_BGSprite(bgTexturePath),
	m_ObjectSet()
{
	m_ObjectSet.insert(&m_Background);
}

GameLevel::~GameLevel()
{
	for (GameObject* obj : m_ObjectSet)
	{
		delete obj;
	}

	m_ObjectSet.clear();
}

void GameLevel::updateAll(float deltaTime)
{
	for (GameObject* obj : m_ObjectSet)
	{
		obj->updateAll(deltaTime);
	}

	update(deltaTime);
}

void GameLevel::draw(ID3D11DeviceContext* deviceContext)
{
	m_Camera.draw(deviceContext);
	m_BGSprite.bind(deviceContext);
	m_Background.draw(deviceContext);

	for (GameObject* obj : m_ObjectSet)
	{
		obj->draw(deviceContext);
	}
}