#include "SonicStopState.h"
#include "Sonic.h"


SonicStopState::SonicStopState(SonicData * playerData)
{
	this->mPlayerData = playerData;
	this->mPlayerData->player->SetVelocityX(50);
}


SonicStopState::~SonicStopState()
{
}

void SonicStopState::update()
{
	if (this->mPlayerData->player->mCurrentAnimate->get()->getCurrentFrameIndex() > 10)
	{
		this->mPlayerData->player->SetVelocityX(0);
	}

	if (this->mPlayerData->player->CheckLastFrame())
		this->mPlayerData->player->SetStateByTag(StateAction::RUN_FAST);
}

SonicState::StateAction SonicStopState::GetState()
{
	return SonicState::STOP;
}
