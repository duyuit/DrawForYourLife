#pragma once
#include "SonicState.h"
class SonicJumpState :public SonicState
{
public:
	SonicJumpState(SonicData *playerData);
	void update();
	int count = 0;
	void handle_swipe(Define::SWIPE_DIRECTION direct);
	void HandleCollision(Sprite* sprite);
	virtual SonicState::StateAction GetState();
	~SonicJumpState();
};

