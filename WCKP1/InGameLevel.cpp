#include "InGameLevel.h"
#include "Input.h"

InGameLevel::InGameLevel(ID3D11Device* device) :
	GameLevel(device, "")
{

}

InGameLevel::~InGameLevel()
{

}

void InGameLevel::update(float deltaTime)
{
	Input& input = *Input::getInstance();
}