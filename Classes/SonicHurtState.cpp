#include "SonicHurtState.h"
#include "Sonic.h"


SonicHurtState::SonicHurtState(SonicData * playerData)
{
	
	this->mPlayerData = playerData;
	
	mPlayerData->player->SetVelocity(0, 0);
	mPlayerData->player->getPhysicsBody()->applyImpulse(Vec2(-200000, 200000));
	lastUpdate = 0;




}

SonicHurtState::~SonicHurtState()
{
}

void SonicHurtState::update()
{
	lastUpdate++;
	if (lastUpdate==60)
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


