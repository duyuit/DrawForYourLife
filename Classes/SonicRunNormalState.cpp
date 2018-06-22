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
		this->mPlayerData->player->SetVelocityX(-200);
	else
		this->mPlayerData->player->SetVelocityX(200);
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
		this->mPlayerData->player->SetStateByTag(StateAction::JUMP);
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

