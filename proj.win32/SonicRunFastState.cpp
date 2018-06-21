#include "SonicRunFastState.h"
#include "Sonic.h"




SonicRunFastState::SonicRunFastState(SonicData * playerData)
{
	this->mPlayerData = playerData;
}

SonicRunFastState::~SonicRunFastState()
{
}

void SonicRunFastState::update()
{
	if (this->mPlayerData->player->isLeft)
		this->mPlayerData->player->velocity.x = -3;
	else
		this->mPlayerData->player->velocity.x = 3;
}

void SonicRunFastState::handle_swipe(Define::SWIPE_DIRECTION direct)
{
	switch (direct)
	{
	case Define::LEFT:
		if (!this->mPlayerData->player->isLeft)
			this->mPlayerData->player->SetStateByTag(StateAction::RUN_SLOW);
		break;
	case Define::RIGHT:
		if (this->mPlayerData->player->isLeft)
			this->mPlayerData->player->SetStateByTag(StateAction::RUN_SLOW);
		break;
	case Define::UP:
		this->mPlayerData->player->SetStateByTag(StateAction::JUMP);
		break;
	case Define::DOWN:
		break;

	default:
		break;
	}
//	last_Swipe = direct;
}

SonicState::StateAction SonicRunFastState::GetState()
{
	return SonicState::RUN_FAST;
}
