#pragma once
#include "SonicState.h"
class SonicRollState :public SonicState
{
public:
	SonicRollState(SonicData *playerData);
	~SonicRollState();
	void update();
	void handle_swipe(Define::SWIPE_DIRECTION direct);
	virtual SonicState::StateAction GetState();
};
