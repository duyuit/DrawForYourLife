#pragma once
#include "Monster.h"
class SharkMonster:public Monster
{
public:
	SharkMonster(Sonic *sonic,Vec2 pos);
	void update(float dt) override;
	void SetStateByTag(MONSTERSTATE state) override;
	bool _flipped = false;
	Sprite* water=nullptr;
	RefPtr<Animate>  *_water_splash;

	bool _isActiveEarly = true;
	bool _isButtonActive = false;
	~SharkMonster();
};

