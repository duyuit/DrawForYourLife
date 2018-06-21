#include "SonicRollState.h"
#include "Sonic.h"




SonicRollState::SonicRollState(SonicData * playerData)
{
	this->mPlayerData = playerData;

}

SonicRollState::~SonicRollState()
{
}

void SonicRollState::update()
{

	if (this->mPlayerData->player->CheckLastFrame())
	{
		this->mPlayerData->player->SetStateByTag(StateAction::RUN_FAST);
		return;
	}
	if (this->mPlayerData->player->isLeft)
		this->mPlayerData->player->velocity.x = -5;
	else
		this->mPlayerData->player->velocity.x = 5;
}

void SonicRollState::handle_swipe(Define::SWIPE_DIRECTION direct)
{
}

SonicState::StateAction SonicRollState::GetState()
{
	return SonicState::ROLL;
}
