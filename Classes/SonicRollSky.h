#pragma once
#include "SonicState.h"
class SonicRollSky :public SonicState
{
public:
	SonicRollSky(SonicData *playerData);
	~SonicRollSky();
	void update();

	void HandleCollision(Sprite* sprite) override;
	virtual SonicState::StateAction GetState();

};

