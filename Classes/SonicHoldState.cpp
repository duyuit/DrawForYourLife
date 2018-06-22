#include "SonicHoldState.h"

#include "Sonic.h"


SonicHoldState::SonicHoldState(SonicData * playerData)
{
	mPlayerData = playerData;
	mPlayerData->player->SetVelocity(0, 0);
}

SonicHoldState::~SonicHoldState()
{
}

void SonicHoldState::update()
{
	count++;
	if (count == 50)
		mPlayerData->player->SetStateByTag(StateAction::JUMP);
}

void SonicHoldState::handle_swipe(Define::SWIPE_DIRECTION direct)
{
}

SonicState::StateAction SonicHoldState::GetState()
{
	return SonicState::HOLD;
}
