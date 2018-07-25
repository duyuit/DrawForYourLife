#pragma once
#include "InfiniteParallaxNode.h"
#include "TapButton.h"
#include "MyUI.h"
#include "SmallRing.h"
#include "BonusChest.h"
#include "FrogMonster.h"
#include "SharkMonster.h"
#include "MyDialogBox.h"
#include "MultipleButton.h"
#include "HoldLand.h"
using namespace cocos2d;
class LevelScene : public cocos2d::Layer
{
public:
	LevelScene();
	~LevelScene();

	Sonic* _mSonic;
	InfiniteParallaxNode *_backgroundNode, *_backgroundNode2;
	CCTMXTiledMap * _tileMap=nullptr;
	MyUI* _myui = nullptr;
	vector<TapButton*> _listButton;
	Vector<Monster*> _listMonster;
	SimpleAudioEngine* audio;
	Vector<MultipleButton*> _listMultipleButton;
	int _speedParallax = 1;

	virtual void MyPause();
	virtual void MyResume();
	virtual void ReloadScene();
	void SortButton();
	void LoadSound();
	void CreateParallaxNode(string path);
	void RollBackground();
	void CheckButton();
	virtual void LoadMap(string path);
	void SetViewPointCenter(Point position, bool isFast);
	bool onContactBegin(cocos2d::PhysicsContact & contact);
	void update(float dt);
	virtual void updateStart(float dt);

	virtual bool init();
	static cocos2d::Scene* createScene();
	CREATE_FUNC(LevelScene);
};
