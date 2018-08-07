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
	Sprite* boss_avatar = nullptr;
	ProgressTimer *mouseBar;



	RefPtr<Animate> * normal_anim;

	RefPtr<Animate> * angry_anim;

	virtual bool init();
	static cocos2d::Scene* createScene();
	void update(float) override;
	void updateStart(float dt) override;
	void ReloadScene() override;
	CREATE_FUNC(BossScene);
};

