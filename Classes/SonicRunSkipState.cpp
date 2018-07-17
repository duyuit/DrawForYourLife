#include "SonicRunSkipState.h"

#include "Sonic.h"


SonicRunSkipState::SonicRunSkipState(SonicData * playerData)
{
	this->mPlayerData = playerData;
	this->mPlayerData->player->SetVelocityX(500);
	MyParticle::CreateWind(this->mPlayerData->player->getPosition(),(Layer*) this->mPlayerData->player->getParent());
}

SonicRunSkipState::~SonicRunSkipState()
{
}

void SonicRunSkipState::update()
{
}

SonicState::StateAction SonicRunSkipState::GetState()
{
	return SonicState::RUNSKIP;
}
