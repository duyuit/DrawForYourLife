#pragma once

#include "InfiniteParallaxNode.h"
#include "TapButton.h"
#include "MyUI.h"
using namespace cocos2d;
class TurtorialScene : public cocos2d::Layer
{
public:
	Vec2 start_touch_position, end_touch_position;
	Sonic* mSonic;
	Vector<TapButton*> listButton;
	InfiniteParallaxNode* _backgroundNode;
	InfiniteParallaxNode* _backgroundNode2;
	CCTMXTiledMap * _tileMap;
	bool isPause = false;
	Vector<Label*> listLabel;
	MyUI* myui;


	int count_tuto = 0;

	Sprite* blackImage;

	TurtorialScene();
	~TurtorialScene();
	void Tutorial1();
	void Tutorial2();
	void Tutorial2_part1();
	void Pause();
	void Continue();
	void LoadMap(CCTMXTiledMap* map);
	void setViewPointCenter(Point position);
	bool onContactBegin(cocos2d::PhysicsContact & contact);
	void update(float dt);
	void updateStart(float dt);

	virtual bool init();
	static cocos2d::Scene* createScene();
	CREATE_FUNC(TurtorialScene);
};

