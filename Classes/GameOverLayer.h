#pragma once
#include "cocos2d.h"
#include "Sonic.h"
using namespace std;
class GameOverLayer : public cocos2d::Layer
{
public:
	GameOverLayer(Sonic* mSonic, Layer* cur_scene, SCENE_LEVELMAP cur_levelmap);
	~GameOverLayer();
	Label* _gameover;
	string font = "fonts/hemi.ttf";
	Sprite* board;
	Layer *current_scene = nullptr;
	SCENE_LEVELMAP currentLevelMap;
	Sonic* mySonic;
	
};

