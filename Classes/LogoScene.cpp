#include "LogoScene.h"
USING_NS_CC;
using namespace std;
using namespace ui;


LogoScene::LogoScene()
{
}


LogoScene::~LogoScene()
{
}


cocos2d::Scene * LogoScene::createScene()
{
	return LogoScene::create();
}

bool LogoScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto background = Sprite::create("Menu/logo.jpg");
	background->setScale(visibleSize.width / (background->getContentSize().width), visibleSize.height / (background->getContentSize().height));
	background->setAnchorPoint(Vec2(0.5, 0.5));
	background->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(background);

	auto actionMoveDone = CallFuncN::create(CC_CALLBACK_1(LogoScene::nextScene, this));
	this->runAction(Sequence::create(DelayTime::create(2.0f), actionMoveDone, NULL));

	return true;
}
void LogoScene::nextScene(cocos2d::Node* sender)
{
	auto sceneMeunu = MenuScene::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(1, sceneMeunu));
}