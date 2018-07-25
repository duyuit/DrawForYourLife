#pragma once
#include "SonicState.h"
class SonicStopState:public SonicState
{
public:
	SonicStopState(SonicData * playerData);
	~SonicStopState();
	void update();
	virtual SonicState::StateAction GetState();
};

