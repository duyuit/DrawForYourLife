#include "SonicRollSky.h"



#include "Sonic.h"
#include "BossLv1.h"
SonicRollSky::SonicRollSky(SonicData * playerData)
{
	this->mPlayerData = playerData;
	//this->mPlayerData->player->getPhysicsBody()->setMass(Define::boss_sonic_mass);
	this->mPlayerData->player->SetVelocityX(0);
	this->mPlayerData->player->getPhysicsBody()->applyForce(Vec2(0, 15500000));
}

SonicRollSky::~SonicRollSky()
{
}

void SonicRollSky::update()
{

}

void SonicRollSky::HandleCollision(Sprite * sprite)
{
	if (sprite->getTag() == Define::land)
	{
		this->mPlayerData->player->SetVelocity(0, 0);
		this->mPlayerData->player->SetStateByTag(StateAction::RUN_FAST);
	}
	if (sprite->getTag() == Define::BOSS)
	{
		this->mPlayerData->player->getPhysicsBody()->applyImpulse(Vec2(0, 500000));
	
		auto boss = (BossLv1*)this->mPlayerData->player->boss;
		if (boss->maximum_hit > 0)
		{
			boss->GenerateButton();
			boss->maximum_hit--;
		}

	}
}

SonicState::StateAction SonicRollSky::GetState()
{
	return SonicState::ROLL_IN_SKY;
}
