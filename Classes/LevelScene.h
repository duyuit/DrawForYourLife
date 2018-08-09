#pragma once
#include "InfiniteParallaxNode.h"
#include "TapButton.h"
#include "MyUI.h"
#include "SmallRing.h"
#include "FinishFlag.h"
#include "BonusChest.h"
#include "FrogMonster.h"
#include "SharkMonster.h"
#include "MyDialogBox.h"
#include "MultipleButton.h"
#include "HoldLand.h"
#include "YetiMonster.h"
#include "LizardMonster.h"
#include "SandRatMonster.h"
#include "SnakeMonster.h"
#include "AnubisMonster.h"

using namespace cocos2d;
class LevelScene : public cocos2d::Layer
{
public:
	LevelScene();
	~LevelScene();

	Sonic* _mSonic;
	InfiniteParallaxNode *_backgroundNode, *_backgroundNode2;
	CCTMXTiledMap * _tileMap = nullptr;
	MyUI* _myui = nullptr;
	vector<TapButton*> _listButton;
	Vector<Monster*> _listMonster;
	Vector<MultipleButton*> _listMultipleButton;
	Vector<BonusChest*> _listBonus;
	int _speedParallax = 1;
	SCENE_LEVELMAP area_1;

	void MyReadyPause();
	void MyReadyResume();
	virtual void MyPause();
	virtual void MyResume();
	virtual void ReloadScene();
	virtual void NextScene();
	void SortButton();
	void CreateParallaxNode(string path);
	void CreateTileLayer(string path);
	void RollBackground();
	void CheckButton();
	virtual void LoadMap(string path);
	void SetViewPointCenter(Point position,Vec2 delta=Vec2(-400,0));
	bool onContactBegin(cocos2d::PhysicsContact & contact);
	void update(float dt);
	virtual void updateStart(float dt);
	void setCurrentArea(SCENE_LEVELMAP sceneLevel);

	virtual bool init();
	static cocos2d::Scene* createScene();
	CREATE_FUNC(LevelScene);
};

