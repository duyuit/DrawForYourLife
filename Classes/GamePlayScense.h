#pragma once
#ifndef __GamePlayScense_H__
#define __GamePlayScense_H__
#include "cocos2d.h"
#include "LevelMap.h"
class GamePlayScense : public cocos2d::Scene
{
public:
	GamePlayScense();
	~GamePlayScense();
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(GamePlayScense);
};
#endif
