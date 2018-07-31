#pragma once
#ifndef __LevelMap_H__
#define __LevelMap_H__
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "TurtorialScene.h"
#include "Level1Scene.h"
#include "LoadScene.h"
#include "SelectMap.h"
USING_NS_CC;
class LevelMap : public cocos2d::Scene
{
public:
	LevelMap();
	~LevelMap();
	Sprite* board;
	int _levelState;
	Label* myLabel;
	Vector<Sprite*> star_list;
	FinishLayer* finishLayer;
	int currentLevel = 0;
	string font = "fonts/hemi.ttf";

	Button* button_level_0;
	Button* button_level_1;
	Button* button_level_2;
	Button* button_level_3;
	Button* button_level_4;
	Button* button_level_5;
	Button* button_level_bonus;

	bool isBoard = false;

	Label*  _label_0;
	Label* _label_1;

	void update(float dt);
	static cocos2d::Scene* createScene();
	virtual bool init();
	void nextScene(cocos2d::Node* sender);
	void setStar(int level, int star);
	CREATE_FUNC(LevelMap);
};
#endif
