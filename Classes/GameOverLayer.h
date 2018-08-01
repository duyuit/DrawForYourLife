#pragma once
#include "cocos2d.h"
#include "Sonic.h"
using namespace std;
class GameOverLayer : public cocos2d::Layer
{
public:
	GameOverLayer(Sonic* mSonic, Layer* cur_scene);
	~GameOverLayer();
	Label* _gameover;
	string font = "fonts/hemi.ttf";
	Sprite* board;
	Layer *current_scene = nullptr;
	Sonic* mySonic;
};

