#include "SonicIdleState.h"
#include "Sonic.h"
SonicIdleState::SonicIdleState(SonicData * playerData)
{
	this->mPlayerData = playerData;
	this->mPlayerData->player->SetVelocityX(0);
}

SonicIdleState::~SonicIdleState()
{
}

void SonicIdleState::update()
{
}

SonicState::StateAction SonicIdleState::GetState()
{
	return SonicState::IDLE;
}
