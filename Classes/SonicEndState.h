#pragma once
#include "SonicState.h"
class SonicEndState:public SonicState
{
public:
	SonicEndState(SonicData *playerData);
	virtual SonicState::StateAction GetState();
	void update();
	float delta = 0;
	~SonicEndState();
};
