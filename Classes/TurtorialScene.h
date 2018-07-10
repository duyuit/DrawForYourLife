#pragma once

#include "InfiniteParallaxNode.h"
#include "TapButton.h"
#include "MyUI.h"
#include "SmallRing.h"
#include "FrogMonster.h"
#include "MyDialogBox.h"
#include "MultipleButton.h"
using namespace cocos2d;
class TurtorialScene : public cocos2d::Layer
{
public:
	Vec2 start_touch_position, end_touch_position;
	Sonic* _mSonic;
	Vector<TapButton*> _listButton;
	Vector<SmallRing*> _listRing;
	Vector<Monster*> _listMonster;
	MyDialogBox* _diabox;

	InfiniteParallaxNode* _backgroundNode;
	InfiniteParallaxNode* _backgroundNode2;
	CCTMXTiledMap * _tileMap;
	bool _isPause = false;
	
	MyUI* _myui=nullptr;

	int count_to_move_scene = 0; // 
	int delta_x = -30; //2 Variable to Shake Camera when sonic is pausing
	int count_tuto =0;

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

	void RollBackground();
	void Pause();
	void Continue();
	void LoadMap(CCTMXTiledMap* map);
	void SetViewPointCenter(Point position,bool isFast);
	bool onContactBegin(cocos2d::PhysicsContact & contact);
	void update(float dt);
	void updateStart(float dt);

	virtual bool init();
	static cocos2d::Scene* createScene();
	CREATE_FUNC(TurtorialScene);
};

