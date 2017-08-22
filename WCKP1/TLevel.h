#pragma once
#include "GameLevel.h"

class TLevel : public GameLevel
{
public:
	TLevel(ID3D11Device* device);

	virtual void update(float deltaTime) override;
private:
};