#include "SonicHurtState.h"
#include "Sonic.h"


SonicHurtState::SonicHurtState(SonicData * playerData)
{
	
	this->mPlayerData = playerData;
	
	mPlayerData->player->SetVelocity(0, 0);
	mPlayerData->player->getPhysicsBody()->applyImpulse(Vec2(-500000, 200000));





}

SonicHurtState::~SonicHurtState()
{
}

void SonicHurtState::update()
{
	if (this->mPlayerData->player->CheckLastFrame())
	{
		this->mPlayerData->player->SetStateByTag(StateAction::RUN_FAST);
		return;
	}
}

void SonicHurtState::handle_swipe(Define::SWIPE_DIRECTION direct)
{
}

SonicState::StateAction SonicHurtState::GetState()
{
	return SonicState::HURT;
}


