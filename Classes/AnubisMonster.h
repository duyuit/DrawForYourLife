#pragma once
#include "Monster.h"
class AnubisMonster : public Monster
{
public:
	AnubisMonster(Sonic *sonic, Vec2 pos);
	void update(float dt) override;
	void SetStateByTag(MONSTERSTATE state) override;

	bool _isActiveEarly = true;
	bool isActive = false;

	AnubisMonster() {};
	~AnubisMonster();

protected:
		RefPtr<Animate>  *_die2Ani;
		RefPtr<Animate>  *_die3Ani;
};

