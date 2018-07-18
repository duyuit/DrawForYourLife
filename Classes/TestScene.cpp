#include "TestScene.h"



TestScene::TestScene()
{


}


TestScene::~TestScene()
{
}

bool TestScene::init()
{
//	int a = 0;
	LevelScene::init();
	string s = "LevelScene/LV1/untitled.tmx";
	LoadMap(s);
	return true;
	
}

cocos2d::Scene * TestScene::createScene()
{
	auto scene = Scene::createWithPhysics();

	// set gravity
	scene->getPhysicsWorld()->setGravity(Vec2(0, -1000));

	// optional: set debug draw
	//scene->getPhysicsWorld()->setDebugDrawMask(0xffff);
	//scene->getPhysicsWorld()->step(1 / 60.0f);



	auto layer = TestScene::create();
	scene->addChild(layer);

	return scene;
}
