#pragma once
#include "cocos2d.h"
#include "Sonic.h"
using namespace cocos2d;

class TapButton:public Sprite
{
public:
	TapButton(Vec2 pos,Sonic *sprite,Layer* layer);
	Sonic* mTarget;
	float _time_dissapear = 0.5;
	float _time_circle_shrink = 1;
	SonicState::StateAction _action = SonicState::JUMP;
	int isLeft;
	int isCountCombo = false;


	RefPtr<Animate>  *_break_Ani;
	BUTTON_TAG mTag;
	bool isDelete=false;
	bool isFirst = false;
	bool isActive = false;
	bool isTrue = false;
	~TapButton();
	void OnSetFirst(bool is);
	void Active();
	void Dissapear();
	void DeleteNow(bool check);
	void update(float dt);
};

