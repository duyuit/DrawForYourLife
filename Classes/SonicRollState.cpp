#include "SonicRollState.h"
#include "Sonic.h"




SonicRollState::SonicRollState(SonicData * playerData)
{
	this->mPlayerData = playerData;
	if (this->mPlayerData->player->isLeft)
		this->mPlayerData->player->SetVelocity(-500, this->mPlayerData->player->GetVelocity().y);
	else
		this->mPlayerData->player->SetVelocity(500, this->mPlayerData->player->GetVelocity().y);

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
	
}

void SonicRollState::handle_swipe(Define::SWIPE_DIRECTION direct)
{
}

SonicState::StateAction SonicRollState::GetState()
{
	return SonicState::ROLL;
}
