#pragma once
#include "cocos2d.h"
#include "Sonic.h"
using namespace cocos2d;
class TapButton:public Sprite
{
public:
	TapButton(int ID,Vec2 pos,Sonic *sprite,Layer* layer);
	Sprite* circle;
	Sonic* mTarget;


	BUTTON_TAG mTag;


	bool can_Active = false;
	bool isActive = false;
	~TapButton();
	void Active();
	void Dissapear();
	void update(float dt);
};

