#include "SonicRunNormalState.h"
#include "Sonic.h"


SonicRunNormalState::SonicRunNormalState(SonicData * playerData)
{
	this->mPlayerData = playerData;
}


SonicRunNormalState::~SonicRunNormalState()
{
}

void SonicRunNormalState::update()
{
	if (this->mPlayerData->player->isLeft)
		this->mPlayerData->player->velocity.x = -2;
	else
		this->mPlayerData->player->velocity.x = 2;
}

void SonicRunNormalState::handle_swipe(Define::SWIPE_DIRECTION direct)
{
	switch (direct)
	{
	case Define::LEFT:
		if (this->mPlayerData->player->isLeft)
			this->mPlayerData->player->SetStateByTag(StateAction::RUN_FAST);
		else this->mPlayerData->player->SetStateByTag(StateAction::RUN_SLOW);
		break;
	case Define::RIGHT:
		if (!this->mPlayerData->player->isLeft)
			this->mPlayerData->player->SetStateByTag(StateAction::RUN_FAST);
		else this->mPlayerData->player->SetStateByTag(StateAction::RUN_SLOW);
		break;
	case Define::UP:
		break;
	case Define::DOWN:
		break;

	default:
		break;
	}
}

SonicState::StateAction SonicRunNormalState::GetState()
{
	return SonicState::RUN_NORMAL;
}

