#pragma once
#include "GameObject.h"

class Horse : public GameObject
{
public:
	Horse(ID3D11Device* device);
	~Horse() = default;

	void update(float deltaTime) override {};
private:
	Sprite m_Sprite;
};