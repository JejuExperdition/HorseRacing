#include "InGameLevel.h"
#include "Input.h"

InGameLevel::InGameLevel(ID3D11Device* device) :
	GameLevel(device, "Background1"),
	m_Horse(device)
{
	addObject(&m_Horse);
}

InGameLevel::~InGameLevel()
{

}

void InGameLevel::update(float deltaTime)
{
	Input& input = *Input::getInstance();
}