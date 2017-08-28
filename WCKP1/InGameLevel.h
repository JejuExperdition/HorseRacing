#pragma once
#include "GameLevel.h"
#include "Horse.h"
#include "Boost.h"

class InGameLevel : public GameLevel
{
public:
	InGameLevel(ID3D11Device* device);
	~InGameLevel();

	void update(float deltaTime) override;

private:
	Horse m_Horse;
	Boost* m_Boosts;
};