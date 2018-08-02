#include "BossScene.h"

#include "BossLv1.h"

BossScene::BossScene()
{
}


BossScene::~BossScene()
{
}

bool BossScene::init()
{
	LevelScene::init();

	auto boss = new BossLv1(Vec2(1100, 317), _mSonic, (Layer*)this);
	//boss->Flip();
	this->addChild(boss);
	boss->SetState(BossLv1::IDLE);



	_mSonic->isFightingBoss = true;
	_mSonic->position_when_FightingBoss = _mSonic->getPosition();



	LoadMap("LevelScene/StoneMap/lv1.tmx");
	//CreateTileLayer("LevelScene/StoneMap/lv1_layer");
	CreateParallaxNode("Map_stone/stone_bg3.png");

	scheduleOnce(CC_SCHEDULE_SELECTOR(BossScene::updateStart), 0);
	return true;
}

cocos2d::Scene * BossScene::createScene()
{
	auto scene = Scene::createWithPhysics();

	// set gravity
	scene->getPhysicsWorld()->setGravity(Vec2(0, -1000));

	// optional: set debug draw
	//scene->getPhysicsWorld()->setDebugDrawMask(0xffff);
	scene->getPhysicsWorld()->step(1 / 60.0f);



	auto layer = BossScene::create();
	scene->addChild(layer);

	return scene;
}

void BossScene::updateStart(float dt)
{
	LevelScene::updateStart(1);
	_myui->current_scene = this;
}
