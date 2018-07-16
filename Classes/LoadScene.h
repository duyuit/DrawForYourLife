#pragma once
#ifndef __LoadScene_H__
#define __LoadScene_H__
#include "cocos2d.h"
#include "LevelMap.h"
USING_NS_CC;
class LoadScene : public cocos2d::Scene
{
public:
	LoadScene();
	~LoadScene();
	static cocos2d::Scene* createScene();
	virtual bool init();
	void nextScene(cocos2d::Node* sender);
	Scene* sceneLevelMap;
	CREATE_FUNC(LoadScene);
};
#endif
