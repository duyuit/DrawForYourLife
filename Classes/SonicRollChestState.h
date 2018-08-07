#pragma once
#include "SonicState.h"
class SonicRollChestState: public SonicState
{
public:
	SonicRollChestState(SonicData *playerData);
	~SonicRollChestState();
	void update();
	void handle_swipe(Define::SWIPE_DIRECTION direct);
	virtual SonicState::StateAction GetState();
	void HandleCollision(Sprite* sprite);
	int _time_action = 0;
};

