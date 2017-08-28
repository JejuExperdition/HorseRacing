#pragma once
#include "GameObject.h"
#include "Horse.h"

class Boost : public GameObject
{
public:
	Boost(const XMFLOAT2& pos);
	Boost(const XMFLOAT2&& pos);

	void update(float deltaTime) override {};
private:
	Sprite m_Sprite;
};