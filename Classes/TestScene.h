#pragma once
#include "InfiniteParallaxNode.h"
#include "TapButton.h"
#include "MyUI.h"
#include "SmallRing.h"
#include "FrogMonster.h"
#include "MyDialogBox.h"
#include "MultipleButton.h"
using namespace cocos2d;
class TestScene : public cocos2d::Layer
{
public:
	TestScene();
	~TestScene();
	Sonic* _mSonic;
	InfiniteParallaxNode* _backgroundNode;
	InfiniteParallaxNode* _backgroundNode2;
	CCTMXTiledMap * _tileMap;
	MyUI* _myui = nullptr;
	Vector<TapButton*> _listButton;
	Vector<Monster*> _listMonster;

	void RollBackground();

	void CheckButton();
	void LoadMap(CCTMXTiledMap* map);
	void SetViewPointCenter(Point position, bool isFast);
	bool onContactBegin(cocos2d::PhysicsContact & contact);
	void update(float dt);
	void updateStart(float dt);
	void ResetTutorial4();
	void ResetTutorial5();
	virtual bool init();
	static cocos2d::Scene* createScene();
	CREATE_FUNC(TestScene);
};

