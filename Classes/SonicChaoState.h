
#pragma once
#include "SonicState.h"
class SonicChaoState:public SonicState
{
public:
	SonicChaoState(SonicData *playerData);
	~SonicChaoState();
	void update();
	virtual SonicState::StateAction GetState();
	void HandleCollision(Sprite* sprite) override;
};

