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
	Sprite* blackImage;
	int count_to_change_position = 0;
	TurtorialScene();
	~TurtorialScene();


	virtual void  ReloadScene() override;
	void Pause();
	void Continue();
	void update(float dt) override;
	void updateStart(float dt) override;
//	bool onContactBegin(cocos2d::PhysicsContact & contact);
	virtual bool init();
	static cocos2d::Scene* createScene();
	CREATE_FUNC(TurtorialScene);
};

