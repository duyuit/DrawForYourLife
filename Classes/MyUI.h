#pragma once
#include "cocos2d.h"
#include "Sonic.h"
#include "ui/CocosGUI.h"
using namespace cocos2d;
using namespace ui;

class MyUI:public Layer
{
public:
	MyUI() {};
	Sonic* mySonic;
	Button *_button_left,*_button_right;
	Sprite* ringIcon;
	Label* countRing;

	void update(float dt)
	{
		countRing->setString("X  " + std::to_string(mySonic->ringCollected));
	}
	void DisableExcept(BUTTON_TAG tag);
	void EnableAll();
	MyUI(Sonic* mSonic);
protected:
	RefPtr<Animate>  *touch_ani;
};