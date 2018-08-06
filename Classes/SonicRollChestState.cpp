#include "SonicRollChestState.h"
#include "Sonic.h"

SonicRollChestState::SonicRollChestState(SonicData * playerData)
{
	this->mPlayerData = playerData;
	this->mPlayerData->player->SetVelocityX(0);
	Define::_music_sonic_roll_effect = experimental::AudioEngine::play2d(Define::_music_sonic_roll_effect_path, false, 1.0f);
	//MyParticle::CreateWind(this->mPlayerData->player->getPosition(), (Layer*) this->mPlayerData->player->getParent());
}

SonicRollChestState::~SonicRollChestState()
{
}

void SonicRollChestState::update()
{
	RepeatForever::create(this->mPlayerData->player->mCurrentAnimate->get());
	this->mPlayerData->player->_roll_effect->setVisible(true);
	/*if (this->mPlayerData->player->mCurrentAnimate->get()->getCurrentFrameIndex() == 0)
	{
		this->mPlayerData->player->_roll_effect->setVisible(true);
		this->mPlayerData->player->mCurrentAnimate->get()->getAnimation()->setRestoreOriginalFrame(true);
		this->mPlayerData->player->mCurrentAnimate->get()->getAnimation()->set
	}*/
	//if (this->mPlayerData->player->CheckLastFrame())

	//if (_time_action >= 180)
	//{
	//	this->mPlayerData->player->_roll_effect->setVisible(false);
	//	SimpleAudioEngine::getInstance()->stopEffect(sound_effect);
	//	this->mPlayerData->player->SetStateByTag(StateAction::RUN_FAST);
	//	return;
	//}
	//_time_action++;
}

void SonicRollChestState::handle_swipe(Define::SWIPE_DIRECTION direct)
{
}

SonicState::StateAction SonicRollChestState::GetState()
{
	_time_action = 0;
	return SonicState::ROLL_CHEST;
}

void SonicRollChestState::HandleCollision(Sprite * sprite)
{
}
