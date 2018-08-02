#include "SonicRollSky.h"



#include "Sonic.h"
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
}

SonicState::StateAction SonicRollSky::GetState()
{
	return SonicState::ROLL_IN_SKY;
}
