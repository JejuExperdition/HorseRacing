#include "BackGround.h"

BackGround::BackGround(ID3D11Device* device, Sprite* spr) :
	GameObject(device, 5760, 2170, 10, spr)
{
	setPosition({ 0, 0 });
}