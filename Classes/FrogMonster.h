#pragma once
#include "Monster.h"
class FrogMonster:public Monster
{
public:
	FrogMonster(Sonic* sonic);
	FrogMonster() {};
	~FrogMonster();
	 //void HandleCollision(Sprite *sprite); //Use to handle collision with object
	 //void update(float dt);
	 //void SetStateByTag(MONSTERSTATE state);
};

