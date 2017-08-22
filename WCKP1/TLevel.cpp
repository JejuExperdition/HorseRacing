#include "TLevel.h"
#include "Input.h"

TLevel::TLevel(ID3D11Device* device) :
	GameLevel(device, "./Down.dds")
{

}

void TLevel::update(float deltaTime)
{
	Input& input = *Input::getInstance();
	if (input.getKey('A') && input.getKey('B'))
	{
		exit(1);
	}
	if (input.getButton(1))
	{
		exit(1);
	}
}