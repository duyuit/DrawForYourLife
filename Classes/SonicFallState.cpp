#include "SonicFallState.h"


#include "Sonic.h"

SonicFallState::SonicFallState(SonicData * playerData)
{
	this->mPlayerData = playerData;
	/*if (this->mPlayerData->player->isLeft)
		this->mPlayerData->player->SetVelocityX(-360);
	else
		this->mPlayerData->player->SetVelocityX(360);*/
}

SonicFallState::~SonicFallState()
{
}

void SonicFallState::update()
{
	//count++;
	//if (abs(mPlayerData->player->GetVelocity().y)<5 && count>30)
	//	mPlayerData->player->SetStateByTag(StateAction::RUN_FAST);

}

void SonicFallState::handle_swipe(Define::SWIPE_DIRECTION direct)
{
}

void SonicFallState::HandleCollision(Sprite * sprite)
{
	if (sprite->getTag() == Define::land)
		this->mPlayerData->player->SetStateByTag(StateAction::RUN_FAST);
}

SonicState::StateAction SonicFallState::GetState()
{
	return SonicState::FALL;
}
