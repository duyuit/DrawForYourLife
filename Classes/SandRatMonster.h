#pragma once
#include "Monster.h"
class SandRatMonster : public Monster
{
public:
	SandRatMonster(Sonic* sonic, Vec2 pos);
	void HandleCollision(Sprite *sprite) override;
	void update(float dt) override;
	void SetStateByTag(MONSTERSTATE state) override;
	SandRatMonster() {};
	~SandRatMonster();
};

