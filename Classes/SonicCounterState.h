#pragma once
#include "SonicState.h"
class SonicCounterState: public SonicState
{
public:
	SonicCounterState(SonicData *playerData);
	~SonicCounterState();

	void update();
	virtual SonicState::StateAction GetState();
};

