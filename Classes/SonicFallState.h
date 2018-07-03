#pragma once
#include "SonicState.h"
class SonicFallState :public SonicState
{
public:
	SonicFallState(SonicData *playerData);
	~SonicFallState();
	void update();
	int count = 0;
	void handle_swipe(Define::SWIPE_DIRECTION direct);
	 void HandleCollision(Sprite* sprite) override;
	virtual SonicState::StateAction GetState();
};


