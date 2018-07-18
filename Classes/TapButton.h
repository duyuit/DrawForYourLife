#pragma once
#include "cocos2d.h"
#include "Sonic.h"
using namespace cocos2d;

class TapButton:public Sprite
{
public:
	TapButton(Vec2 pos,Sonic *sprite,Layer* layer);
	Sonic* mTarget;
	SonicState::StateAction _action = SonicState::JUMP;
	int isLeft;
	int isCountCombo = false;
	float time = 1.4;
	ProgressTimer* mouseBar;
	Sprite* _border;
	Sprite* _progressbar;

	RefPtr<Animate>  *_break_Ani;
	BUTTON_TAG mTag = NONE;
	bool isDelete=false;
	bool canActive = false;
	bool isActive = false;
	bool isTrue = false;
	~TapButton();
	void CheckLabel(float percen);
	void SetCanActive(bool is);
	void Active();
	void DeleteNow(bool check);
	void update(float dt);
protected:

	Label* _label; //Perfect, Great, Bad
};

