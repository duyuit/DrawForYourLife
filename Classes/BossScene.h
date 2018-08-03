#pragma once
#include "LevelScene.h"

#include "BossLv1.h"
class BossScene:public LevelScene
{
public:
	BossScene();
	~BossScene();

	BossLv1* boss;
	virtual bool init();
	static cocos2d::Scene* createScene();
	void update(float) override;
	void updateStart(float dt) override;
	void ReloadScene() override;
	CREATE_FUNC(BossScene);
};

