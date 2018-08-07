#include "SonicRollSky.h"



#include "Sonic.h"
#include "BossLv1.h"
SonicRollSky::SonicRollSky(SonicData * playerData)
{
	this->mPlayerData = playerData;
	//this->mPlayerData->player->getPhysicsBody()->setMass(Define::boss_sonic_mass);
	this->mPlayerData->player->SetVelocityX(0);
	//this->mPlayerData->player->getPhysicsBody()->applyForce(Vec2(0, 15500000));
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
		auto boss = (BossLv1*)this->mPlayerData->player->boss;
		if (boss->isCrazy)
		{
			boss->drill->stopAllActions();
			boss->plane->stopAllActions();
			this->mPlayerData->player->getPhysicsBody()->applyImpulse(Vec2(0, 800000));
			this->mPlayerData->player->_roll_effect->setRotation(-90);
			this->mPlayerData->player->_roll_effect->setPosition(this->mPlayerData->player->_roll_effect->getPosition() +Vec2(-100,50));
			this->mPlayerData->player->SetStateByTag(SonicState::ROLL_CHEST);
			return;
		}
		this->mPlayerData->player->SetVelocity(0, 0);
		this->mPlayerData->player->SetStateByTag(StateAction::RUN_FAST);

	}
	if (sprite->getTag() == Define::BOSS)
	{
		auto boss = (BossLv1*)this->mPlayerData->player->boss;
		boss->GetDame();
		this->mPlayerData->player->getPhysicsBody()->applyImpulse(Vec2(0, 500000));
	
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
