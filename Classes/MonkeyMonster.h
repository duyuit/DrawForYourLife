#pragma once
#include "Monster.h"
class MonkeyMonster: public Monster
{
public:
	MonkeyMonster(Sonic *sonic, Vec2 pos);
	~MonkeyMonster();

	void update(float dt) override;
	void SetStateByTag(MONSTERSTATE state) override;

	bool _isActiveEarly = true;
	bool isActive = false;
};

