#include "BackGround.h"

BackGround::BackGround(ID3D11Device* device, Texture* tex) :
	GameObject(device, 1920, 1080, 10, tex)
{
	setPosition({ 0, 0 });
}