#pragma once
#include "SonicState.h"
class SonicJumpState :public SonicState
{
public:
	SonicJumpState(SonicData *playerData);
	SonicJumpState(SonicData *playerData,int count);
	void update();
	int count = 0;
	void handle_swipe(Define::SWIPE_DIRECTION direct);
	virtual SonicState::StateAction GetState();
	~SonicJumpState();
};

