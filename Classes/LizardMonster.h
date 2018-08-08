#pragma once
#include "Monster.h"
class LizardMonster : public Monster
{
public:
	LizardMonster(Sonic* sonic);
	void SetStateByTag(MONSTERSTATE state) override;
	LizardMonster() {};
	~LizardMonster();

};

