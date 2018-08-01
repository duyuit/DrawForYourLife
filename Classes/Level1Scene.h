#pragma once
#include "LevelScene.h"
#include "MonkeyMonster.h"
#include "BossLv1.h"
class Level1Scene:public LevelScene
{
public:
	Level1Scene();
	~Level1Scene();
	BossLv1 *boss;
	void NextScene() override;
	void LoadMap(string path) override;
	virtual void  ReloadScene() override;
	void Pause();
	void Continue();
	void update(float dt) override;
	void updateStart(float dt) override;
	bool onContactBegin(cocos2d::PhysicsContact & contact);
	virtual bool init();
	static cocos2d::Scene* createScene();
	CREATE_FUNC(Level1Scene);
};

