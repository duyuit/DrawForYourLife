#include "SonicHurtState.h"
#include "Sonic.h"


SonicHurtState::SonicHurtState(SonicData * playerData)
{
	
	this->mPlayerData = playerData;
	
	mPlayerData->player->SetVelocity(0, 0);
	mPlayerData->player->getPhysicsBody()->applyImpulse(Vec2(-500000, 200000));


	if ( mPlayerData->player->ringCollected > 0 &&  mPlayerData->player->baseLife > 0)
	{
		int t =  mPlayerData->player->ringCollected; //Temp variable
		for (int i = 0; i < (int)(t /  mPlayerData->player->baseLife); i++)
		{
			//mPlayerData->player->runAction(CallFuncN::create(CC_CALLBACK_0(SonicHurtState::DropRing, this)));
			DropRing();
			mPlayerData->player->ringCollected--;
		}
		 mPlayerData->player->baseLife--;
	}
	else if ( mPlayerData->player->ringCollected <= 0 ||  mPlayerData->player->baseLife <= 0)
	{
		 mPlayerData->player->ringCollected = 0;
		 mPlayerData->player->baseLife = 2;
	}


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



void SonicHurtState::DropRing()
{
	auto ring = new SmallRing();
	//ring->setPosition(0, 0);
	ring->setPosition(mPlayerData->player->getPosition()+Vec2(0,100));
	//ring->setPosition(Director::getInstance()->getWinSize);
	ring->getPhysicsBody()->setDynamic(true);
	ring->getPhysicsBody()->setGravityEnable(true);

	ring->getPhysicsBody()->setCollisionBitmask(2);

	float x = RandomHelper::random_real(-1.0, 1.0);
	float y = RandomHelper::random_real(0.0, 10.0);

	ring->getPhysicsBody()->setVelocity(Vec2(0, 0));
	ring->getPhysicsBody()->applyForce(Vec2(-3000000 * x, 800000 * y));
	ring->getPhysicsBody()->setContactTestBitmask(1);
	ring->SetAutoRemove();
	auto  temp=	mPlayerData->player->getParent();
	mPlayerData->player->getParent()->addChild(ring, 10);
}