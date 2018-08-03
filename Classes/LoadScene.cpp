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
Scene * LoadScene::createScene()
{
	auto scene = LoadScene::create();
	//switch (name)
	//{
	//case Define::TUTO:
	//	scene->nextScene = TurtorialScene::createScene();
	//	break;
	//case Define::LV1:
	//	scene->nextScene = Level1Scene::createScene();
	//	break;
	//default:
	//	break;
	//}
	return scene;

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

	mouseBar->runAction(ProgressFromTo::create(1.0f, 0.0f, 100));



	scheduleOnce(CC_SCHEDULE_SELECTOR(LoadScene::updateStart), 0);
	return true;
}

void LoadScene::NextScene()
{
	//Director::getInstance()->replaceScene(TransitionFade::create(1, TurtorialScene::createScene()));

	if ((SCENE_NAME)next_scene == Define::LV0) {
		Director::getInstance()->replaceScene(TransitionFade::create(1, TurtorialScene::createScene()));
	}
	if ((SCENE_NAME)next_scene == Define::LV1 && (SCENE_AREA)next_scene_area == Define::DESERT) {
		Director::getInstance()->replaceScene(TransitionFade::create(1, Level1Scene::createSceneArea(Define::DESERT)));
	}
	if ((SCENE_NAME)next_scene == Define::LV1 && (SCENE_AREA)next_scene_area == Define::SNOW) {
		Director::getInstance()->replaceScene(TransitionFade::create(1, Level1Scene::createSceneArea(Define::SNOW)));
	}
	if ((SCENE_NAME)next_scene == Define::LV1 && (SCENE_AREA)next_scene_area == Define::STONE) {
		Director::getInstance()->replaceScene(TransitionFade::create(1, Level1Scene::createSceneArea(Define::STONE)));
	}

}

void LoadScene::updateStart(float dt)
{
	auto actionMoveDone = CallFuncN::create(CC_CALLBACK_0(LoadScene::NextScene, this));
	this->runAction(Sequence::create(DelayTime::create(2.0), actionMoveDone, NULL));
}

