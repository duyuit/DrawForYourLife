#pragma once
#include "cocos2d.h"
#include "Sonic.h"
#include "ui/CocosGUI.h"
#include "RingComboScore.h"

using namespace cocos2d;
using namespace ui;

class MyUI :public Layer
{
public:
	MyUI() {};
	Layer *current_scene = nullptr;
	Sonic* mySonic;
	Button *_button_left, *_button_right, *_restart;
	Sprite* _touch_guide;
	RingComboScore* _combo;
	Sprite* board;
	LayerColor *layer = nullptr;

	bool _istouch = false;
	int count_to_reset_touch = 0;

	void DisableExcept(BUTTON_TAG tag);
	void EnableAll();
	MyUI(Sonic* mSonic);

	void update(float dt);
protected:
	RefPtr<Animate>  *touch_ani;
};