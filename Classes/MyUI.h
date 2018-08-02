#pragma once
#include "cocos2d.h"
#include "Sonic.h"
#include "ui/CocosGUI.h"
#include "RingComboScore.h"
#include "FinishLayer.h"
#include "GameOverLayer.h"
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

	//bool isPause=false;
	void SetCurrentScene(Layer* scene);
	FinishLayer* finish = nullptr;

	string font = "fonts/hemi.ttf";
	GameOverLayer* gameover = nullptr;

	bool _istouch = false;
	int count_to_reset_touch = 0;
	int count_to_change_position = 0;
	int count_to_finish = 0;
	int count_to_gameover = 0;

	void DisableExcept(BUTTON_TAG tag);
	void EnableAll();

	MyUI(Sonic* mSonic);

	void update(float dt);
protected:
	RefPtr<Animate>  *touch_ani;
};