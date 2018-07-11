#pragma once
#ifndef __LevelMap_H__
#define __LevelMap_H__
#include "cocos2d.h"
#include "ui/CocosGUI.h"
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

	static cocos2d::Scene* createScene();
	virtual bool init();
	void nextScene(cocos2d::Node* sender);
	void LevelMap::setStar(int level, int star);
	CREATE_FUNC(LevelMap);
};
#endif
