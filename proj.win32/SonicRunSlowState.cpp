#include "SonicRunSlowState.h"
#include "proj.win32\Sonic.h"




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
		this->mPlayerData->player->velocity.x = -1;
	else
		this->mPlayerData->player->velocity.x = 1;
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


