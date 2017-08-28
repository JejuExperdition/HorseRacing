#pragma once
#include "GameObject.h"

class Horse : public GameObject
{
public:
	Horse(ID3D11Device* device);
	~Horse() = default;

	void update(float deltaTime) override;

	using GameObject::getAngle;
	using GameObject::getPosition;
private:
	Sprite m_Sprite;
	bool m_IsMoving;
	float m_Direction;
	int m_Speed;
};