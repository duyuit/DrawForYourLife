#pragma once
#include "SonicState.h"
class SonicRollState :public SonicState
{
public:
	int roll_sound = 0;
	SonicRollState(SonicData *playerData);
	~SonicRollState();
	void update();
	void handle_swipe(Define::SWIPE_DIRECTION direct);
	virtual SonicState::StateAction GetState();
	void HandleCollision(Sprite* sprite);
};
