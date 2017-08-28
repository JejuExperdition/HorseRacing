#include "BackGround.h"

BackGround::BackGround(ID3D11Device* device, Sprite* spr) :
	GameObject(device, 6500, 3000, 10, spr)
{
	setPosition({ 0, 0 });
}