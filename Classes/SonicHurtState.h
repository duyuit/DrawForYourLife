#pragma once
#include "SonicState.h"
class SonicHurtState :public SonicState
{
public:
	SonicHurtState(SonicData *playerData);
	~SonicHurtState();
	void update();

	void handle_swipe(Define::SWIPE_DIRECTION direct);
	virtual SonicState::StateAction GetState();


};


