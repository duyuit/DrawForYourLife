#include "SonicJumpState.h"
#include "Sonic.h"



SonicJumpState::SonicJumpState(SonicData * playerData)
{
	this->mPlayerData = playerData;
	this->mPlayerData->player->getPhysicsBody()->applyForce(Vec2(0, 13000000));
	if (this->mPlayerData->player->isLeft)
		this->mPlayerData->player->SetVelocityX(-360);
	else
		this->mPlayerData->player->SetVelocityX(360);

}



void SonicJumpState::update()
{

	if (this->mPlayerData->player->getPhysicsBody()->getVelocity().y < -5 || this->mPlayerData->player->CheckLastFrame())
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
		//this->mPlayerData->player->SetState(new SonicJumpState(this->mPlayerData,2));
		break;
	case Define::DOWN:
		break;

	default:
		break;
	}
}

void SonicJumpState::handle_collision(Sprite * sprite)
{
	if (sprite->getTag() == Define::HoldPlace)
	{
		this->mPlayerData->player->setPosition(sprite->getPosition());
		this->mPlayerData->player->SetStateByTag(SonicState::StateAction::HOLD);
	}
}

SonicState::StateAction SonicJumpState::GetState()
{
	return SonicState::JUMP;
}

SonicJumpState::~SonicJumpState()
{
}
