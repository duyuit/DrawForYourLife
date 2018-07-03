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
	float time_dissapear = 0.3;

	BUTTON_TAG mTag;
	bool isDelete=false;
	bool isFirst = false;
	bool can_Active = false;
	bool isActive = false;
	~TapButton();
	void Active();
	void Dissapear();
	void DeleteNow();
	void DeleteCircle();
	void update(float dt);
};

