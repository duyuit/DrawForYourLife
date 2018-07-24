#pragma once
#include "GameDefine.h"
#include "TapButton.h"
using namespace cocos2d;
class HoldLand:public Sprite
{
public:
	HoldLand(Vec2 pos, Size size,bool isLeft, Sonic* sonic,Layer* layer);
	TapButton* _tapButton;
	void Active();
	bool isActive = false;
	~HoldLand();
};

