#pragma once
#include "cocos2d.h"
#include "GameDefine.h"
using namespace cocos2d;

class small_Ring:public Sprite
{
public:
	small_Ring();
	~small_Ring();
	RefPtr<Animate>  *roll;
};

