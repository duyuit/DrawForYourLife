#include "TurtorialScene.h"
#include "Level1Scene.h"
#include "LoadScene.h"
cocos2d::Scene * TurtorialScene::createScene()
{
	auto scene = Scene::createWithPhysics();

	// set gravity
	scene->getPhysicsWorld()->setGravity(Vec2(0, -1000));

	// optional: set debug draw
//	scene->getPhysicsWorld()->setDebugDrawMask(0xffff);
	scene->getPhysicsWorld()->step(1 / 60.0f);



	auto layer = TurtorialScene::create();
	scene->addChild(layer);

	return scene;
}


void TurtorialScene::LoadMap(string path)
{
	LevelScene::LoadMap(path);

	
	//SortButton();
}

TurtorialScene::TurtorialScene()
{
}


TurtorialScene::~TurtorialScene()
{
	//autorelease();
}



void TurtorialScene::NextScene()
{
	auto scene =(LoadScene*) LoadScene::createScene();
	scene->next_scene = (int)Define::LV1;

	Director::getInstance()->replaceScene(scene);
}

void TurtorialScene::ReloadScene()
{
	Director::getInstance()->replaceScene(this->createScene());
}

void TurtorialScene::Pause()
{
	_mSonic->SetVelocity(0,0);
	_isPause = true;
	_diabox->setVisible(true);
	_diabox->setPosition(_mSonic->getPositionX(), _director->getWinSize().height*3/4);

	blacklayer->setVisible(true);
}

void TurtorialScene::Continue()
{
	if(count_tuto==4)
		_listMultipleButton.at(0)->scheduleUpdate();
	if (count_tuto == 5)
		_listBonus.at(0)->_multiButton->scheduleUpdate();
	if (count_tuto == 2 && !_listButton.at(0)->isTrue)
		return;
	_isPause = false;
	_mSonic->SetVelocityX(340);
	_diabox->setVisible(false);
	blacklayer->setVisible(false);
}





void TurtorialScene::update(float dt)
{
	if (_mSonic->isDelete)
	Director::getInstance()->replaceScene(this->createScene());
	LevelScene::update(dt);

	if (_isPause)
		_mSonic->SetVelocityX(0);
	if(_myui!=nullptr)
	if (_myui->_istouch && _isPause)
		Continue();

	if (count_tuto == 0 && !_isPause && _listButton.at(0)->getPositionX() - _mSonic->getPositionX() <= 800)
	{
		count_tuto++;
		Pause();
		_diabox->UpdateString("Look! There's a button.\nIt'll activate when you go close enough.");
		_listButton.at(0)->time = 100;
		_diabox->SetTapToContinue(true);
	}
	if (count_tuto == 1 && !_isPause && _listButton.at(0)->isActive)
	{
		count_tuto++;
		Pause();
		_diabox->UpdateString("Tap left or right to do actions. \nThe faster you tap, the more score you get.");
		_diabox->SetTapToContinue(false);
		_myui->DisableExcept(_listButton.at(0)->mTag);
	}
	if (count_tuto == 2 && _listButton.at(0)->isTrue && !_listButton.at(0)->isDelete)
	{
		Continue();
		_myui->EnableAll();
		_listMultipleButton.at(0)->unscheduleUpdate();
		count_tuto++;
	}
	if (count_tuto == 3 && _listMultipleButton.at(0)->getPositionX() - _mSonic->getPositionX()<=600)
	{
		Pause();
		_diabox->UpdateString("Look! There's a frog.\nPress a sequence button to go through.");
	
		count_tuto++;
	}
	if (count_tuto == 4 && _listBonus.at(0)->getPositionX() - _mSonic->getPositionX() <= 800)
	{
	
		Pause();
		
		_diabox->UpdateString("When you activate the chest, tap as fast as\nyou can to get more rings");
	
		count_tuto++;
	}
	if (count_tuto == 5 && _listBonus.at(0)->_multiButton->isTrue)
	{
		_myui->_touch_guide->setVisible(true);
		count_to_change_position++;
		if (count_to_change_position == 10)
		{
			if (_myui->_touch_guide->getPositionX() != (_director->getWinSize().width / 3) / 2)
				_myui->_touch_guide->setPosition((_director->getWinSize().width / 3) / 2, _director->getWinSize().height / 2);
			else _myui->_touch_guide->setPosition(_director->getWinSize().width - _director->getWinSize().width / 6, _director->getWinSize().height / 2);
			count_to_change_position = 0;
		}
		if (_listBonus.at(0)->_isDelete)
		{
			count_tuto++;
			_myui->_touch_guide->setVisible(false);
		}
	}


}

void TurtorialScene::updateStart(float dt)
{
	LevelScene::updateStart(1);
	_myui->current_scene = this;
	blacklayer = LayerColor::create(Color4B::BLACK);
	blacklayer->setOpacity(100);
	this->getScene()->addChild(blacklayer);


}



bool TurtorialScene::init()
{
	LevelScene::init();
	
	LoadMap("LevelScene/StoneMap/tutorial.tmx");
	CreateTileLayer("LevelScene/StoneMap/tutorial");
	CreateParallaxNode("Map_stone/stone_bg3.png");
	SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	SimpleAudioEngine::getInstance()->playBackgroundMusic(Define::_music_stone_background_2_path, true);
	_listBonus.at(0)->_multiButton->unscheduleUpdate();


	_diabox = new MyDialogBox();
	_diabox->setPosition(1500, 400);
	_diabox->SetScale(0.7);
	_diabox->SetTapToContinue(false);

	this->addChild(_diabox, 7);

	_mSonic->setPosition(1000, 200);

	
	
	
	SetViewPointCenter(_mSonic->getPosition());
	_mSonic->setZOrder(7);


	
	//Listener
	{
		auto listener1 = EventListenerTouchOneByOne::create();

		listener1->onTouchBegan = [this](Touch* touch, Event* event) {
		
			return true;
		};

		// trigger when you let up
		listener1->onTouchEnded = [this](Touch* touch, Event* event) {
			Continue();
		};
		_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, this);
	}

	scheduleOnce(CC_SCHEDULE_SELECTOR(TurtorialScene::updateStart), 0);
	Pause();
	_diabox->UpdateString("Welcome to Sonic's world");
	_diabox->SetTapToContinue(true);

	return true;
}

