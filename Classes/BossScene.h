#pragma once
#include "LevelScene.h"
class BossScene:public LevelScene
{
public:
	BossScene();
	~BossScene();


	virtual bool init();
	static cocos2d::Scene* createScene();
	void updateStart(float dt) override;
	CREATE_FUNC(BossScene);
};

