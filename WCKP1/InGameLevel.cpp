#include "InGameLevel.h"
#include "Input.h"

InGameLevel::InGameLevel(ID3D11Device* device) :
	GameLevel(device, "Background1"),
	m_Horse(device),
	m_Boosts(new Boost({ 500, 500 }))
{
	addObject(&m_Horse);
	addObject(m_Boosts);
}

InGameLevel::~InGameLevel()
{
	delete m_Boosts;
}

void InGameLevel::update(float deltaTime)
{
	Input& input = *Input::getInstance();

	getCamera().setAngle(m_Horse.getAngle() + XM_PIDIV2);
	getCamera().setPosition(m_Horse.getPosition());
}