#pragma once
#include "cocos2d.h"
#include "MenuScene.h"
#include "SimpleAudioEngine.h"
#ifndef __LogoScene_H__
#define __LogoScene_H__

class LogoScene : public cocos2d::Scene
{
public:
	LogoScene();
	~LogoScene();

	SimpleAudioEngine* audio = SimpleAudioEngine::getInstance();
	void LoadSound();
	static cocos2d::Scene* createScene();
	void nextScene(cocos2d::Node* sender);
	virtual bool init();
	CREATE_FUNC(LogoScene);
};
#endif