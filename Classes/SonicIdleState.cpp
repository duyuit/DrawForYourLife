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
	if ((abs)(this->mPlayerData->player->getPositionX() - this->mPlayerData->player->position_when_FightingBoss.x) >20)
	{
		this->mPlayerData->player->SetStateByTag(RUN_FAST);
	}
}

SonicState::StateAction SonicIdleState::GetState()
{
	return SonicState::IDLE;
}
