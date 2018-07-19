#pragma once
#include "Monster.h"
class SharkMonster:public Monster
{
public:
	SharkMonster(Sonic *sonic);
	void update(float dt) override;
	void SetStateByTag(MONSTERSTATE state) override;
	bool _flipped = false;
	~SharkMonster();
};

