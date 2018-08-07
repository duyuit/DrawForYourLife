#pragma once
#include "LevelScene.h"
#include "MonkeyMonster.h"
#include "BossLv1.h"
class Level1Scene:public LevelScene
{
public:
	Level1Scene();
	~Level1Scene();

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
	static cocos2d::Scene* createSceneArea(SCENE_AREA next_scene_area, SCENE_NAME levelScene);

	CREATE_FUNC(Level1Scene);
};

