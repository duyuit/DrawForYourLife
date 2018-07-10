
#include "GamePlayScense.h"
USING_NS_CC;
using namespace std;
using namespace ui;
GamePlayScense::GamePlayScense()
{
}


GamePlayScense::~GamePlayScense()
{
}

cocos2d::Scene * GamePlayScense::createScene()
{
	return GamePlayScense::create();
}

bool GamePlayScense::init()
{
	if (!Scene::init())
	{
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto background = Sprite::create("game_board.png");
	background->setScale(visibleSize.width / (background->getContentSize().width), visibleSize.height / (background->getContentSize().height));
	background->setAnchorPoint(Vec2(0.5, 0.5));
	background->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(background, 0);
	return true;
}
