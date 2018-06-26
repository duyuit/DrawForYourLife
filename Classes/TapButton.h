#pragma once
#include "cocos2d.h"
using namespace cocos2d;
class TapButton:public Sprite
{
public:
	TapButton(int ID,Vec2 pos,Sprite *sprite,Layer* layer);
	Sprite* circle;
	Sprite* mTarget;
	bool isActive = false;
	~TapButton();
	void Active();
	void update(float dt);
};

