#pragma once
#include <cocos2d.h>
#include "Sonic.h"
#include "GameDefine.h"
#include <vector>
using namespace cocos2d;
class MultipleButton:public Node 
{
public:
	MultipleButton();
	MultipleButton(Vec2 pos,Sonic* sonic,Layer* layer,int button_count, float time);
	int _button_count = 3;
	float _time = 1.5f;
	bool isActive = false;
	bool isCountCombo = false;
	bool canActive = false;

	int count_to_auto_play = 0;

	void update(float dt);
	Sprite* _border;
	Sprite* _progressbar;

	Sonic* _mSonic;
	std::vector<int> _list_button_tag;
	Vector<Sprite*> _list_button_sprite;
	SonicState::StateAction _action;
	bool isDelete = false;

	RefPtr<Animate>  *_break_left_Ani;
	RefPtr<Animate>  *_break_right_Ani;
	

	void Active();
	void DeleteNow(bool check);
	void BlinkProgressBar();
	~MultipleButton();
protected:
	ProgressTimer* mouseBar;
	void CheckLabel(float percen); 
	Label* _label; //Perfect, Great, Bad
};

