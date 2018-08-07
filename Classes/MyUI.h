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
	LayerColor *layer_1 = nullptr;
	SCENE_LEVELMAP currentLevelMap;
	SCENE_LEVELMAP currentArea;
	SCENE_NAME currentLevel;
	Label* labelStart;

	void SetCurrentScene(Layer* scene);
	FinishLayer* finish = nullptr;

	string font = "fonts/hemi.ttf";
	GameOverLayer* gameover = nullptr;

	bool _istouch = false;
	int count_to_reset_touch = 0;
	int count_to_change_position = 0;
	int count_to_finish = 0;
	int count_to_gameover = 0;

	int count_ready = 0;
	int count_start = 0;
	int count_number = 0;
	bool isReady = true;
	bool isStart = false;
	bool isCount = false;
	bool isDone = false;
	bool isTurnOnMusic1 = false;
	bool isTurnOnMusic2 = false;
	bool isCallPause = false;

	void setCurrentLevelMap(SCENE_LEVELMAP sceneLevel);
	void setCurrentLevel(SCENE_NAME level);
	void DisableExcept(BUTTON_TAG tag);
	void EnableAll();

	MyUI(Sonic* mSonic);

	void update(float dt);
protected:
	RefPtr<Animate>  *touch_ani;
};