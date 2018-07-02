#pragma once

#include "InfiniteParallaxNode.h"
#include "TapButton.h"
#include "MyUI.h"
#include "SmallRing.h"
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

	int count_to_move_scene = 0; // 
	int delta_x = -30; //2 Variable to Shake Camera when sonic is pausing
	int count_tuto = 0;

	Sprite* blackImage;

	TurtorialScene();
	~TurtorialScene();
	void Tutorial1();

	void Tutorial2();
	void Tutorial2_part1();

	void Tutorial3();
	void Tutorial3_part1();

	void Tutorial4();
	void Tutorial4_part1();
	
	void RollBackground();
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

class TarGetCircle:public Sprite
{
public:
	TarGetCircle(float scale_first,Vec2 pos)
	{
		this->initWithFile("Button/circle.png");
		this->setScale(scale_first);
		this->setColor(Color3B(255, 255, 132));
		this->setPosition(pos);
		this->setZOrder(8);

	


		

	
	};
	void RunAction()
	{
		auto fadeOut = FadeOut::create(0.1f);
		auto reverse = fadeOut->reverse();
		ActionInterval *fade = Sequence::create(fadeOut, reverse, nullptr);
		auto fading = RepeatForever::create(fade);
		this->runAction(fading);

	


	}

	~TarGetCircle() {};
};