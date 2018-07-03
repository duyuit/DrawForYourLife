#include "SonicState.h"



SonicState::SonicState()
{
}
SonicState::StateAction SonicState::GetState()
{
	return RUN_SLOW;
}

void SonicState::update()
{
}

void SonicState::handle_swipe(Define::SWIPE_DIRECTION direct)
{
}

void SonicState::HandleCollision(Sprite * sprite)
{
	return;
}


SonicState::SonicState(SonicData *playerData)
{
	this->mPlayerData = playerData;
}
SonicState::~SonicState()
{
}
