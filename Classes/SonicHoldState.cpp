#include "SonicHoldState.h"

#include "Sonic.h"


SonicHoldState::SonicHoldState(SonicData * playerData)
{
	mPlayerData = playerData;

	mPlayerData->player->getPhysicsBody()->setGravityEnable(false);
	mPlayerData->player->SetVelocity(0, 0);
	mPlayerData->player->isLeft = !mPlayerData->player->isLeft;
}

SonicHoldState::~SonicHoldState()
{
}

void SonicHoldState::update()
{
	count++;
	if (count ==70)
	{
		mPlayerData->player->getPhysicsBody()->setGravityEnable(true);
		mPlayerData->player->DisableCurrentButton();
		mPlayerData->player->SetStateByTag(StateAction::FALL);
		return;
	}


}

void SonicHoldState::handle_swipe(Define::SWIPE_DIRECTION direct)
{
}

SonicState::StateAction SonicHoldState::GetState()
{
	return SonicState::HOLD;
}
