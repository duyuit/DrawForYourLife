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

	Label*  _label_0;
	Label* _label_1;

	static cocos2d::Scene* createScene();
	virtual bool init();
	void nextScene(cocos2d::Node* sender);
	void setStar(int level, int star);
	CREATE_FUNC(LevelMap);
};
#endif
