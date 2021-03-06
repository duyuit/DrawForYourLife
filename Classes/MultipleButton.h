#pragma once
#include <cocos2d.h>
#include "Sonic.h"
#include "GameDefine.h"
#include <vector>
#include "TapButton.h"
using namespace cocos2d;
class MultipleButton:public Node 
{
public:
	MultipleButton();
	MultipleButton(Vec2 pos,Sonic* sonic,Layer* layer,int button_count, float time, int del_button);
	int _button_count = 3;
	float _time = 1.5f;
	bool isActive = false;
	bool isCountCombo = false;
	bool canActive = false;
	bool isTrue = false; 
	int count_to_auto_play = 0;
	string font = "fonts/hemi.ttf";
	TYPE_SCORE score;
	void update(float dt);
	Sprite* _border;
	Sprite* _progressbar;

	Sonic* _mSonic;
	std::vector<int> _list_button_tag;
	Vector<Sprite*> _list_button_sprite;
	SonicState::StateAction _action;
	bool isDelete = false;
	int del_button_pos_1 = -1;
	int del_button_pos_2 = -1;

	int current_button = 0;
	RefPtr<Animate>  *_break_left_Ani;
	RefPtr<Animate>  *_break_right_Ani;
	void ActiveButton(BUTTON_TAG dir);
	void Active();
	void DeleteNow(bool check);
	void BlinkProgressBar();
	~MultipleButton();
protected:
	ProgressTimer* mouseBar;
	void CheckLabel(float percen, bool check); 
	Label* _label; //Perfect, Great, Bad
};

