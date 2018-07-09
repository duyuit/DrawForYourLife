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
	MultipleButton(Sonic* sonic,int button_count, float time);
	int _button_count = 3;
	float _time = 1.5f;
	bool isActive = false;

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
};

