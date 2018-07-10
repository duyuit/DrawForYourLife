#pragma once
#include "cocos2d.h"
#include "Sonic.h"
using namespace cocos2d;

class TapButton:public Sprite
{
public:
	TapButton(Vec2 pos,Sonic *sprite,Layer* layer);
	Sprite* circle;
	Sonic* mTarget;
	float _time_dissapear = 0.5;
	float _time_circle_shrink = 1;
	SonicState::StateAction _action = SonicState::JUMP;
	int isLeft;


	RefPtr<Animate>  *_break_Ani;
	
	BUTTON_TAG mTag;
	bool isDelete=false;
	bool isFirst = false;
	bool can_Active = false;
	bool isActive = false;
	~TapButton();
	void Active();
	void Dissapear();
	void DeleteNow(bool check);
	void DeleteCircle();
	void update(float dt);
};

