#include "SonicFallState.h"


#include "Sonic.h"
#include "HoldLand.h"

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
	if (abs(mPlayerData->player->GetVelocity().y)<5 && count>30)
		mPlayerData->player->SetStateByTag(StateAction::RUN_FAST);

}

void SonicFallState::handle_swipe(Define::SWIPE_DIRECTION direct)
{
}

void SonicFallState::HandleCollision(Sprite * sprite)
{
	if (sprite->getTag() == Define::land)
	{
		this->mPlayerData->player->SetVelocity(340, 0);
		this->mPlayerData->player->SetStateByTag(StateAction::RUN_FAST);
	}
	else 
	if (sprite->getTag() == Define::HoldPlace)
	{
		HoldLand *hold = (HoldLand*)sprite;
		if (!hold->isActive)
		{
			hold->Active();
			this->mPlayerData->player->setPosition(sprite->getPosition());
			this->mPlayerData->player->SetStateByTag(SonicState::StateAction::HOLD);
			
		}
	}
}

SonicState::StateAction SonicFallState::GetState()
{
	return SonicState::FALL;
}
