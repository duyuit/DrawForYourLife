#include "LoadScene.h"
#include "TestScene.h"
#include "TurtorialScene.h"
#include "Level1Scene.h"
USING_NS_CC;
using namespace std;
using namespace ui;
LoadScene::LoadScene()
{
}

LoadScene::~LoadScene()
{
}
cocos2d::Scene * LoadScene::createScene()
{
	return LoadScene::create();
}

bool LoadScene::init()
{
	if (!Scene::init())
	{
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto loading = Sprite::create("Menu/sonic_loading.png");
	loading->setScale(visibleSize.width / loading->getContentSize().width, visibleSize.height / loading->getContentSize().height);
	loading->setAnchorPoint(Vec2(0.5, 0.5));
	loading->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(loading, 0);

	float scaleX = visibleSize.width / loading->getContentSize().width;
	float scaleY = visibleSize.height / loading->getContentSize().height;

	Sprite* border = Sprite::create("Menu/loading_bar.png");
	border->setScale(3.5*scaleX, 1.03*scaleY);
	border->setAnchorPoint(Vec2(0.5, 0.5));
	border->setPosition(Vec2(0.0, 0.0));
	this->addChild(border, 5);

	Sprite* background = Sprite::create("Menu/loadingfull_bar.png");
	background->setScale(3.5*scaleX, 1.03*scaleY);
	background->setAnchorPoint(Vec2(0.5, 0.5));

	ProgressTimer* mouseBar = ProgressTimer::create(background);
	mouseBar->setType(ProgressTimerType::BAR);
	mouseBar->setAnchorPoint(Vec2(0.0, 0.0));
	mouseBar->setPosition(Vec2(0.0, 0.0));
	mouseBar->setBarChangeRate(Vec2(1, 0));
	mouseBar->setMidpoint(Vec2(0.0, 0.0));
	mouseBar->setPercentage(90);
	border->addChild(mouseBar, 10);




	auto actionMoveDone = CallFuncN::create(CC_CALLBACK_1(LoadScene::nextScene, this));
	mouseBar->runAction(ProgressFromTo::create(1.0f, 0.0f, 100));
	this->runAction(Sequence::create(DelayTime::create(2.0), actionMoveDone, NULL));
	return true;
}

void LoadScene::nextScene(cocos2d::Node* sender)
{
	sceneLevelMap = Level1Scene::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(1, sceneLevelMap));

}

