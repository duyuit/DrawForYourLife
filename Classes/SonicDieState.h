#pragma once
#include "SonicState.h"
class SonicDieState: public SonicState
{
public:
	SonicDieState(SonicData *playerData);
	void update();
	virtual SonicState::StateAction GetState();
	~SonicDieState();
};

