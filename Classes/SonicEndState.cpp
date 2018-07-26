#include "SonicEndState.h"

#include "Sonic.h"
SonicEndState::SonicEndState(SonicData * playerData)
{
	this->mPlayerData = playerData;
}

SonicState::StateAction SonicEndState::GetState()
{
	return SonicState::END;
}

void SonicEndState::update()
{
	delta += 0.05;
	if (this->mPlayerData->player->GetVelocity().x > 0)
		this->mPlayerData->player->SetVelocityX(this->mPlayerData->player->GetVelocity().x - delta);
}

SonicEndState::~SonicEndState()
{
}
