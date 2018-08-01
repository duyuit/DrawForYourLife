#include "SonicRollSky.h"



#include "Sonic.h"
SonicRollSky::SonicRollSky(SonicData * playerData)
{
	this->mPlayerData = playerData;
	this->mPlayerData->player->getPhysicsBody()->applyForce(Vec2(0, 20500000));
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
		this->mPlayerData->player->SetVelocity(340, 0);
		this->mPlayerData->player->SetStateByTag(StateAction::ROLL_IN_SKY);
	}
}

SonicState::StateAction SonicRollSky::GetState()
{
	return SonicState::ROLL_IN_SKY;
}
