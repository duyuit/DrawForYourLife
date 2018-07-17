#include "SonicDieState.h"
#include "Sonic.h"


SonicDieState::SonicDieState(SonicData * playerData)
{
	this->mPlayerData = playerData;
	this->mPlayerData->player->setTextureRect(Rect(1632,3220,164,178));

}

void SonicDieState::update()
{
}

SonicState::StateAction SonicDieState::GetState()
{
	return SonicState::DIE;
}

SonicDieState::~SonicDieState()
{
}
