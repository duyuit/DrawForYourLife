#include "SonicRollState.h"
#include "Sonic.h"




SonicRollState::SonicRollState(SonicData * playerData)
{
	this->mPlayerData = playerData;
	if (this->mPlayerData->player->isLeft)	this->mPlayerData->player->SetVelocityX(-500);
	else
		this->mPlayerData->player->SetVelocityX(500);
	roll_sound = experimental::AudioEngine::play2d(Define::_music_sonic_roll_effect_path, false, 1.0f);
	MyParticle::CreateWind(this->mPlayerData->player->getPosition(), (Layer*) this->mPlayerData->player->getParent());
}

SonicRollState::~SonicRollState()
{
}

void SonicRollState::update()
{
	if (this->mPlayerData->player->mCurrentAnimate->get()->getCurrentFrameIndex() == 10)
	{
		this->mPlayerData->player->_roll_effect->setVisible(true);
		this->mPlayerData->player->SetVelocityX(700);
	}
	if (this->mPlayerData->player->CheckLastFrame())
	{
		this->mPlayerData->player->_roll_effect->setVisible(false);
		experimental::AudioEngine::stop(roll_sound);
		this->mPlayerData->player->SetStateByTag(StateAction::RUN_FAST);
		return;
	}
	
}

void SonicRollState::handle_swipe(Define::SWIPE_DIRECTION direct)
{

}

SonicState::StateAction SonicRollState::GetState()
{
	return SonicState::ROLL;
}

void SonicRollState::HandleCollision(Sprite * sprite)
{

}
