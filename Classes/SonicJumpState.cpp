#include "SonicJumpState.h"
#include "Sonic.h"



SonicJumpState::SonicJumpState(SonicData * playerData)
{
	this->mPlayerData = playerData;
	this->mPlayerData->player->getPhysicsBody()->applyForce(Vec2(0, 15000000));
	if (this->mPlayerData->player->isLeft)
		this->mPlayerData->player->SetVelocityX(-360);
	else
		this->mPlayerData->player->SetVelocityX(360);

}

SonicJumpState::SonicJumpState(SonicData * playerData, int count)
{
	this->mPlayerData = playerData;
	if (count > 0)
	{
		this->mPlayerData->player->getPhysicsBody()->applyForce(Vec2(0, 10000000));
		//this->mPlayerData->player->getPhysicsBody()->setVelocity(Vec2(0, 1));
	}


}

void SonicJumpState::update()
{

	if (this->mPlayerData->player->getPhysicsBody()->getVelocity().y < 0 || this->mPlayerData->player->CheckLastFrame())
		this->mPlayerData->player->SetStateByTag(SonicState::FALL);
	
}

void SonicJumpState::handle_swipe(Define::SWIPE_DIRECTION direct)
{
	switch (direct)
	{
	case Define::LEFT:
		break;
	case Define::RIGHT:
		break;
	case Define::UP:
		this->mPlayerData->player->SetState(new SonicJumpState(this->mPlayerData,2));
		break;
	case Define::DOWN:
		break;

	default:
		break;
	}
}

SonicState::StateAction SonicJumpState::GetState()
{
	return SonicState::JUMP;
}

SonicJumpState::~SonicJumpState()
{
}
