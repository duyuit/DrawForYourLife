#pragma once
#include "cocos2d.h"
#include "GameDefine.h"
#include "MultipleButton.h"
using namespace cocos2d;

class BonusChest: public Sprite
{
public:
	BonusChest() {};
	BonusChest(Sonic * sonic);
	RefPtr<Animate> *open_Ani;
	MultipleButton* _multiButton;

	Sonic* _mSonic;
	int _time_to_open = 0;
	bool _isActive = false, _isCreateRing = true;
	BUTTON_TAG _prev_tap = NONE;
	void Open();
	void CreateRing();

	void update(float dt);
	~BonusChest();
};

