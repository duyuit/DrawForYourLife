#pragma once
#include "cocos2d.h"
#include "GameDefine.h"
using namespace cocos2d;

class SmallRing:public Sprite
{
public:
	SmallRing();
	~SmallRing();
	RefPtr<Animate>  *roll;
};

