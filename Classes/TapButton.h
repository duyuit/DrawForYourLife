#pragma once
#include "cocos2d.h"
#include "Sonic.h"
using namespace cocos2d;
enum TYPE_SCORE
{
	PERFECT,
	GREAT,
	BAD
};
class TapButton:public Sprite
{
public:
	TapButton(Vec2 pos,Sonic *sprite,Layer* layer);
	TapButton(Vec2 pos, Sonic *sprite, Layer* layer,bool isLeft);
	Sonic* mTarget;
	SonicState::StateAction _action = SonicState::JUMP;
	int isLeft;
	int isCountCombo = false;
	float time = 1.4;
	TYPE_SCORE score;
	ProgressTimer* mouseBar;
	Sprite* _border;
	Sprite* _progressbar;
	string font = "fonts/hemi.ttf";

	void ActiveButton(BUTTON_TAG dir);
	RefPtr<Animate>  *_break_Ani=nullptr;
	BUTTON_TAG mTag = NONE;
	
	bool use_for_Hold = false;
	bool isDelete=false;
	bool canActive = false;
	bool isActive = false;
	bool isTrue = false;
	~TapButton();
	void CheckLabel(float percen, bool check);
	void SetCanActive(bool is);
	void Active();
	void DeleteNow(bool check);
	void update(float dt);
protected:

	Label* _label; //Perfect, Great, Bad
};

