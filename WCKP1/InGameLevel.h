#pragma once
#include "GameLevel.h"
#include "Horse.h"

class InGameLevel : public GameLevel
{
public:
	InGameLevel(ID3D11Device* device);
	~InGameLevel();

	void update(float deltaTime) override;

private:
	Horse m_Horse;
};