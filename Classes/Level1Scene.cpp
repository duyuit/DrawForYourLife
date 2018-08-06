﻿#include "Level1Scene.h"
#include "LoadScene.h"
//int area;
Level1Scene::Level1Scene()
{
}


Level1Scene::~Level1Scene()
{
}

void Level1Scene::NextScene()
{
	auto scene = (LoadScene*)LoadScene::createScene();
	scene->next_scene = (int)Define::LV0;

	Director::getInstance()->replaceScene(scene);
}

void Level1Scene::LoadMap(string path)
{
	LevelScene::LoadMap(path);



	TMXObjectGroup *objectGroup_hold_land_left = _tileMap->getObjectGroup("HoldLandLeft");


	for (int i = 0; i < objectGroup_hold_land_left->getObjects().size(); i++)
	{

		Value objectemp = objectGroup_hold_land_left->getObjects().at(i);

		float wi_box = objectemp.asValueMap().at("width").asFloat();
		float he_box = objectemp.asValueMap().at("height").asFloat();
		float x_box = objectemp.asValueMap().at("x").asFloat() + wi_box / 2;
		float y_box = objectemp.asValueMap().at("y").asFloat() + he_box / 2;
		HoldLand* hold = new HoldLand(Vec2(x_box, y_box), Size(wi_box, he_box), true, _mSonic, this);
		
	}

	TMXObjectGroup *objectGroup_hold_land_right = _tileMap->getObjectGroup("HoldLandRight");


	for (int i = 0; i < objectGroup_hold_land_right->getObjects().size(); i++)
	{

		Value objectemp = objectGroup_hold_land_right->getObjects().at(i);

		float wi_box = objectemp.asValueMap().at("width").asFloat();
		float he_box = objectemp.asValueMap().at("height").asFloat();
		float x_box = objectemp.asValueMap().at("x").asFloat() + wi_box / 2;
		float y_box = objectemp.asValueMap().at("y").asFloat() + he_box / 2;
		HoldLand* hold = new HoldLand(Vec2(x_box, y_box), Size(wi_box, he_box), false, _mSonic, this);

	}


	TMXObjectGroup *objectGroup_monkey = _tileMap->getObjectGroup("Monkey");


	for (int i = 0; i < objectGroup_monkey->getObjects().size(); i++)
	{

		Value objectemp = objectGroup_monkey->getObjects().at(i);

		float wi_box = objectemp.asValueMap().at("width").asFloat();
		float he_box = objectemp.asValueMap().at("height").asFloat();
		float x_box = objectemp.asValueMap().at("x").asFloat() + wi_box / 2;
		float y_box = objectemp.asValueMap().at("y").asFloat() + he_box / 2;
		MonkeyMonster *mon = new MonkeyMonster(_mSonic, Vec2(x_box, y_box));
		_listMultipleButton.pushBack(mon->_multiButton);
		this->addChild(mon);
	}
	
	SortButton();
}

void Level1Scene::ReloadScene()
{
	Director::getInstance()->replaceScene(this->createScene());
}

void Level1Scene::Pause()
{
}

void Level1Scene::Continue()
{
}

void Level1Scene::update(float dt)
{
	if (_mSonic->isDelete)
		Director::getInstance()->replaceScene(this->createScene());
	LevelScene::update(dt);
	
}

void Level1Scene::updateStart(float dt)
{
	LevelScene::updateStart(1);
	_myui->current_scene = this;
}

bool Level1Scene::onContactBegin(cocos2d::PhysicsContact & contact)
{
	return false;
}

bool Level1Scene::init()
{
	LevelScene::init();

	//auto boss = new BossLv1(Vec2(1100, 317),_mSonic,(Layer*)this);
	////boss->Flip();
	//this->addChild(boss);
	//boss->SetState(BossLv1::RUN);

	//_mSonic->isFightingBoss = true;
	//_mSonic->position_when_FightingBoss = _mSonic->getPosition();

	experimental::AudioEngine::stopAll();

	if (area == Define::DESERT) {
		//Map Desert
		LoadMap("Map_desert/desert_map.tmx");
		CreateTileLayer("Map_desert/desert_map");
		CreateParallaxNode("Map_desert/desert_bg.png");	
		Define::_music_desert_background_1 = experimental::AudioEngine::play2d(Define::_music_desert_background_1_path, true, 0.8f);
	}
	if (area == Define::SNOW) {
		//Map Snow
		LoadMap("Map_snow/snowmap.tmx");
		CreateTileLayer("Map_snow/snowmap");
		CreateParallaxNode("Map_snow/background.png");
		Define::_music_snow_background_1 = experimental::AudioEngine::play2d(Define::_music_snow_background_1_path, true, 0.8f);
	}
	if (area == Define::STONE) {
		//Map Stone
		LoadMap("LevelScene/StoneMap/lv1.tmx");
		CreateTileLayer("LevelScene/StoneMap/lv1_layer");
		CreateParallaxNode("Map_stone/stone_bg3.png");
		Define::_music_stone_background_1 = experimental::AudioEngine::play2d(Define::_music_stone_background_1_path, true, 0.8f);
	}

	/*LoadMap("LevelScene/StoneMap/lv1.tmx");
	CreateTileLayer("LevelScene/StoneMap/lv1_layer");
	CreateParallaxNode("Map_stone/stone_bg3.png");*/

	scheduleOnce(CC_SCHEDULE_SELECTOR(Level1Scene::updateStart), 0);
	return true;
}

cocos2d::Scene * Level1Scene::createScene()
{
	auto scene = Scene::createWithPhysics();

	// set gravity
	scene->getPhysicsWorld()->setGravity(Vec2(0, -1000));

	// optional: set debug draw
	//scene->getPhysicsWorld()->setDebugDrawMask(0xffff);
	scene->getPhysicsWorld()->step(1 / 60.0f);



	auto layer = Level1Scene::create();
	scene->addChild(layer);

	return scene;
}

cocos2d::Scene * Level1Scene::createSceneArea(SCENE_AREA next_scene_area)
{
	area = (SCENE_AREA)next_scene_area;
	auto scene = Scene::createWithPhysics();

	// set gravity
	scene->getPhysicsWorld()->setGravity(Vec2(0, -1000));

	// optional: set debug draw
	//scene->getPhysicsWorld()->setDebugDrawMask(0xffff);
	scene->getPhysicsWorld()->step(1 / 60.0f);



	auto layer = Level1Scene::create();
	scene->addChild(layer);

	return scene;
}