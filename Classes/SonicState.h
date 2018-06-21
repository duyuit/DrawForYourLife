#include "SonicData.h"
#include "GameDefine.h"

#pragma once
class SonicState
{
public:
	enum StateAction
	{
		RUN_SLOW,
		RUN_NORMAL,
		RUN_FAST,
		JUMP,
		ROLL
	};
	SonicState();
	~SonicState();
	virtual StateAction GetState() = 0;
	virtual void update();
	virtual void handle_swipe(Define::SWIPE_DIRECTION direct);
protected:
	
	SonicState(SonicData *playerData);
	SonicData *mPlayerData;
	float lastUpdate = 0;
};

