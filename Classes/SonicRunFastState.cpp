#include "SonicRunFastState.h"
#include "Sonic.h"




SonicRunFastState::SonicRunFastState(SonicData * playerData)
{
	this->mPlayerData = playerData;
	this->mPlayerData->player->SetVelocityX(340);
}

SonicRunFastState::~SonicRunFastState()
{
}

void SonicRunFastState::update()
{
	this->mPlayerData->player->SetVelocityX(0);
	if (this->mPlayerData->player->GetVelocity().y < -5)
		this->mPlayerData->player->SetStateByTag(SonicState::StateAction::FALL);
}

void SonicRunFastState::handle_swipe(Define::SWIPE_DIRECTION direct)
{
	switch (direct)
	{
	case Define::LEFT:
		//if (!this->mPlayerData->player->isLeft)
			this->mPlayerData->player->SetVelocityX(-340);
			//this->mPlayerData->player->SetStateByTag(StateAction::RUN_SLOW);
		break;
	case Define::RIGHT:
		//if (this->mPlayerData->player->isLeft)
			//this->mPlayerData->player->SetStateByTag(StateAction::RUN_SLOW);
		this->mPlayerData->player->SetVelocityX(340);
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
