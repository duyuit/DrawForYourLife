#pragma once

#include "LevelScene.h"
class TurtorialScene : public LevelScene
{
public:
	MyDialogBox* _diabox;
	bool _isPause = false;
	
	int count_to_move_scene = 0; // 
	int delta_x = -30; //2 Variable to Shake Camera when sonic is pausing
	int count_tuto =0;
	void LoadMap(string path) override;
	LayerColor* blacklayer = nullptr;
	int count_to_change_position = 0;
	TurtorialScene();
	~TurtorialScene();

	void NextScene() override;
	void ReloadScene() override;
	void Pause();
	void Continue();
	void update(float dt) override;
	void updateStart(float dt) override;
//	bool onContactBegin(cocos2d::PhysicsContact & contact);
	virtual bool init();
	static cocos2d::Scene* createScene();
	static cocos2d::Scene* createSceneArea(SCENE_AREA next_scene_area, SCENE_NAME levelScene);
	CREATE_FUNC(TurtorialScene);
};

