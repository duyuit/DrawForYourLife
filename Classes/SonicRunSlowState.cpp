#include "SonicRunSlowState.h"
#include "Sonic.h"




SonicRunSlowState::SonicRunSlowState(SonicData * playerData)
{
	this->mPlayerData = playerData;
}

SonicRunSlowState::~SonicRunSlowState()
{
}

void SonicRunSlowState::update()
{
	
	if(this->mPlayerData->player->isLeft)
		this->mPlayerData->player->SetVelocityX(-100);
	else
		this->mPlayerData->player->SetVelocityX(100);
}

void SonicRunSlowState::handle_swipe(Define::SWIPE_DIRECTION direct)
{
	switch (direct)
	{
	case Define::LEFT:
		if (this->mPlayerData->player->isLeft)
			this->mPlayerData->player->SetStateByTag(StateAction::RUN_NORMAL);
			break;
	case Define::RIGHT:
		if (!this->mPlayerData->player->isLeft)
			this->mPlayerData->player->SetStateByTag(StateAction::RUN_NORMAL);
		break;
	case Define::UP:
		this->mPlayerData->player->SetStateByTag(StateAction::JUMP);
		break;
	case Define::DOWN:
		break;

	default:
		break;
	}
	
}

SonicState::StateAction SonicRunSlowState::GetState()
{
	return SonicState::RUN_SLOW;
}


