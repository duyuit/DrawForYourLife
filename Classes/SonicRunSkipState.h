#pragma once
#include "SonicState.h"
class SonicRunSkipState :public SonicState
{
public:
	SonicRunSkipState(SonicData *playerData);
	~SonicRunSkipState();
	void update();
	virtual SonicState::StateAction GetState();
};

