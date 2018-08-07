#pragma once
#include "LevelScene.h"

#include "BossLv1.h"
class BossScene:public LevelScene
{
public:
	BossScene();
	~BossScene();
	ParticleSystemQuad* test=nullptr;
	LayerColor* blacklayer;
	BossLv1* boss;
	virtual bool init();

	void update(float) override;
	void updateStart(float dt) override;
	void ReloadScene() override;
	static cocos2d::Scene* createScene();
	static cocos2d::Scene* createSceneArea(SCENE_AREA next_scene_area, SCENE_NAME levelScene);
	CREATE_FUNC(BossScene);
};

