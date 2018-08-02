#pragma once
#include "SonicState.h"
class SonicIdleState:public SonicState
{
public:
	SonicIdleState(SonicData *playerData);
	~SonicIdleState();
	void update();
	virtual SonicState::StateAction GetState();
};

