#pragma once
#include "LevelScene.h"

using namespace cocos2d;
class TestScene : public LevelScene
{
public:
	TestScene();
	~TestScene();
	bool init() override;
	static cocos2d::Scene* createScene();
	CREATE_FUNC(TestScene);
};

