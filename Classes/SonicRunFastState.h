#pragma once
#include "SonicState.h"
class SonicRunFastState :public SonicState
{
public:
	SonicRunFastState(SonicData *playerData);
	~SonicRunFastState();
	void update();
	void handle_swipe(Define::SWIPE_DIRECTION direct);
	virtual SonicState::StateAction GetState();
};


