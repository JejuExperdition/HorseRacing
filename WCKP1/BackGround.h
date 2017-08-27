#pragma once
#include "GameObject.h"

class BackGround : public GameObject
{
public:
	BackGround(ID3D11Device* device, Sprite* spr);

	virtual void update(float deltaTime) override {}
};