#pragma once
#include "SonicState.h"
class SonicRunNormalState :public SonicState
{
public:
	SonicRunNormalState(SonicData *playerData);
	~SonicRunNormalState();
	void update();
	void handle_swipe(Define::SWIPE_DIRECTION direct);
	virtual SonicState::StateAction GetState();
};



