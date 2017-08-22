#include "GameLevel.h"

GameLevel::GameLevel(ID3D11Device* device, const char* bgTexturePath):
	m_Camera(device),
	m_Background(device, &m_BGTexture),
	m_BGTexture(device, bgTexturePath),
	m_ObjectSet()
{

}

GameLevel::~GameLevel()
{
	for (GameObject* obj : m_ObjectSet)
	{
		delete obj;
	}

	m_ObjectSet.clear();
}

void GameLevel::draw(ID3D11DeviceContext* deviceContext)
{
	m_Camera.draw(deviceContext);
	m_BGTexture.bind(deviceContext);
	m_Background.draw(deviceContext);

	for (GameObject* obj : m_ObjectSet)
	{
		obj->draw(deviceContext);
	}
}