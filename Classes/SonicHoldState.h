#pragma once
#include "SonicState.h"
class SonicHoldState :public SonicState
{
public:
	SonicHoldState(SonicData *playerData);
	~SonicHoldState();
	void update();
	int count = 0;
	void handle_swipe(Define::SWIPE_DIRECTION direct);
	virtual SonicState::StateAction GetState();
	
};
