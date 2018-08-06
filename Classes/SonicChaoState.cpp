#include "SonicChaoState.h"
#include "Sonic.h"
SonicChaoState::SonicChaoState(SonicData *playerData)
{
	this->mPlayerData = playerData;
	

}


SonicChaoState::~SonicChaoState()
{
}

void SonicChaoState::update()
{
	if (mPlayerData->player->mCurrentAnimate->get()->getCurrentFrameIndex() > 10)
		mPlayerData->player->SetVelocity(0, 0);
}

SonicState::StateAction SonicChaoState::GetState()
{
	return SonicState::CHAOS;
}

void SonicChaoState::HandleCollision(Sprite * sprite)
{
}
