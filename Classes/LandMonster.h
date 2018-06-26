#pragma once
#include "cocos2d.h"
#include "GameDefine.h"


using namespace cocos2d;
class LandMonster:public Sprite
{
public:
	LandMonster();
	~LandMonster();
	void update(float dt);
	RefPtr<Animate>  *move_ani;
	int count_to_move = 0;
	Vec2 velocity = Vec2(3,0);
};

