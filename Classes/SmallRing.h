#pragma once
#include "cocos2d.h"
#include "GameDefine.h"
using namespace cocos2d;

class SmallRing:public Sprite
{
public:
	SmallRing();
	~SmallRing();
	int _time_to_eat = 0;
	RefPtr<Animate>  *roll;
	void SetAutoRemove();
	void update(float dt);
};

