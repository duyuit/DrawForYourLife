#include "SonicCounterState.h"


#include "Sonic.h"

#include "Coconut_Monkey.h"
#include "Pyramid_Anubis.h"
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
		sprite->getPhysicsBody()->removeFromWorld();
		//sprite->getPhysicsBody()->resetForces();
		auto coconut = (Coconut_Monkey*)sprite;
		coconut->ComeBack();
		//	sprite->setRotation(0);
		/*sprite->setPosition(this->mPlayerData->player->getPosition() + Vec2(0, 100));
		sprite->getPhysicsBody()->applyImpulse(Vec2(0, 500000));*/
	}
	if (sprite->getTag() == Define::PYRAMID)
	{
		sprite->getPhysicsBody()->removeFromWorld();
		auto pyramid = (Pyramid_Anubis*)sprite;
		pyramid->ComeBack();
	}
}
