#include "BackGround.h"

BackGround::BackGround(ID3D11Device* device, Sprite* spr) :
	GameObject(device, 1920, 1080, 10, spr)
{
	setPosition({ 0, 0 });
}