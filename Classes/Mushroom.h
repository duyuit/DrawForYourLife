#pragma once
#include "cocos2d.h"

using namespace cocos2d;
class Mushroom:public Sprite
{
public:
	Mushroom();
	~Mushroom();
	RefPtr<Animate>  *push_Ani;
	bool _isActive = false;
	void Active();

};

