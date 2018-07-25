#pragma once
#include "cocos2d.h"
#include "Sonic.h"
#include "ui/CocosGUI.h"
#include "ComboScore.h"

using namespace cocos2d;
using namespace ui;

class MyUI:public Layer
{
public:
	MyUI() {};
	Layer *current_scene = nullptr;
	Sonic* mySonic;
	Button *_button_left,*_button_right,*_restart;
	Sprite* ringIcon;
	Label* countRing;
	Sprite* _touch_guide;
	ComboScore* _combo;	
	Sprite* board;
	LayerColor *layer = nullptr;

	bool _istouch = false;
	int count_to_reset_touch = 0;
	void update(float dt)
	{
		count_to_reset_touch++;
		if (count_to_reset_touch == 10)
		{
			count_to_reset_touch = 0;
			_istouch = false;
		}
		countRing->setString("X  " + std::to_string(mySonic->ringCollected));
	}
	void DisableExcept(BUTTON_TAG tag);
	void EnableAll();
	MyUI(Sonic* mSonic);
protected:
	RefPtr<Animate>  *touch_ani;
};