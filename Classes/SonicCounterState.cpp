#include "SonicCounterState.h"


#include "Sonic.h"


SonicCounterState::SonicCounterState(SonicData * playerData)
{
	this->mPlayerData = playerData;
	this->mPlayerData->player->SetVelocityX(0);
	//this->mPlayerData->player->setAnchorPoint(Vec2(0.5, 0.5));
}

SonicCounterState::~SonicCounterState()
{
}

void SonicCounterState::update()
{
	if (this->mPlayerData->player->CheckLastFrame())
		this->mPlayerData->player->SetStateByTag(SonicState::RUN_FAST);
}

SonicState::StateAction SonicCounterState::GetState()
{
	return SonicState::COUNTER;
}

void SonicCounterState::HandleCollision(Sprite * sprite)
{
	if (sprite->getTag() == Define::COCONUT)
	{
		sprite->getPhysicsBody()->applyImpulse(Vec2(0, -100000));
	}
}
