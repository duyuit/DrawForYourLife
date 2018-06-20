#pragma once
#include "SonicState.h"
class SonicRunSlowState :public SonicState
{
public:
	SonicRunSlowState(SonicData *playerData);
	~SonicRunSlowState();
	void update();
	void handle_swipe(Define::SWIPE_DIRECTION direct);
	virtual SonicState::StateAction GetState();
};

