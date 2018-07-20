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

	TurtorialScene();
	~TurtorialScene();
	void Tutorial1();

	void Tutorial2();
	void Tutorial2_part1();

	void Tutorial3();
	void Tutorial3_part1();

	void Tutorial4();
	void ResetTutorial4();
	void ResetTutorial5();

	void Pause();
	void Continue();
	void update(float dt);
	bool onContactBegin(cocos2d::PhysicsContact & contact);
	virtual bool init();
	static cocos2d::Scene* createScene();
	CREATE_FUNC(TurtorialScene);
};

