
#pragma once
#include "cocos2d.h"
#include "GameDefine.h"
using namespace cocos2d;
class Monster:public Sprite
{
public:
	Monster();
	void SetStateByTag();
	bool m_isLeft = false;
	~Monster();
	
};

