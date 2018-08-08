#pragma once
#include "Monster.h"
class SnakeMonster : public Monster
{
public:
	SnakeMonster(Sonic* sonic);
	void update(float dt) override;
	void SetStateByTag(MONSTERSTATE state) override;
	bool isAttack = true;
	SnakeMonster() {};
	~SnakeMonster();
};

