#include "TurtorialScene.h"

cocos2d::Scene * TurtorialScene::createScene()
{
	auto scene = Scene::createWithPhysics();

	// set gravity
	scene->getPhysicsWorld()->setGravity(Vec2(0, -1000));

	// optional: set debug draw
	//scene->getPhysicsWorld()->setDebugDrawMask(0xffff);
	scene->getPhysicsWorld()->step(1 / 60.0f);



	auto layer = TurtorialScene::create();
	scene->addChild(layer);

	return scene;
}


TurtorialScene::TurtorialScene()
{
}


TurtorialScene::~TurtorialScene()
{
}

void TurtorialScene::Tutorial1()
{
	Pause();
	_myui->setVisible(true);
	_diabox->UpdateString("Look! There's a secret button on your screen\nit will active when you close enought");
	

}

void TurtorialScene::Tutorial2()
{
	_diabox->UpdateString("Now you can see direction of button, and a timer.\nPress more soon,more score for you");
//	_listButton.at(0)->mouseBar->stopAllActions();
	_listButton.at(0)->time = 100;
	Pause();
	
	
}

void TurtorialScene::Tutorial2_part1()
{
	_diabox->UpdateString("You must press on left or right on screen\n to interact with button");
	_diabox->SetTapToContinue(false);
	BUTTON_TAG temp = _listButton.at(0)->mTag;
	_myui->DisableExcept(_listButton.at(0)->mTag);
	count_tuto++;
	Pause();
}



void TurtorialScene::Tutorial3()
{
	Pause();
	_diabox->UpdateString("Wait...");
	_diabox->SetTapToContinue(false);

	_myui->DisableExcept(_listButton.at(1)->mTag);
	_listButton.at(1)->unscheduleUpdate();
}

void TurtorialScene::Tutorial3_part1()
{
	_diabox->UpdateString("Tap now!!!!");
	_diabox->SetTapToContinue(false);
	
	_listButton.at(1)->scheduleUpdate();
}

void TurtorialScene::Tutorial4()
{
	_diabox->UpdateString("Good! Let's try another one!");
	_diabox->SetTapToContinue(true);
	_myui->DisableExcept(_listButton.at(2)->mTag);
	Pause();
}
void TurtorialScene::ResetTutorial4()
{

	_mSonic->setPosition(5000,600);
	TapButton *tap= new TapButton(_listButton.at(3)->getPosition(), _mSonic, this);
//	tap->isFirst = true;
	_listButton.erase(_listButton.begin() + 3);
//	_listButton.insert(3, tap);
	Pause();
	SetViewPointCenter(_mSonic->getPosition(), true);
	_diabox->UpdateString("Oops. Let's try again!");
}

void TurtorialScene::ResetTutorial5()
{
	_mSonic->setPosition(9400, 600);
	
	TapButton *tap = new TapButton(_listButton.at(6)->getPosition(), _mSonic, this);
	//tap->isFirst = true;
	_listButton.erase(_listButton.begin() + 6);
	//_listButton.insert(6, tap);

	TapButton *tap2 = new TapButton(_listButton.at(7)->getPosition(), _mSonic, this);
	//tap2->isFirst = true;
	_listButton.erase(_listButton.begin() + 7);
	//_listButton.insert(7, tap2);


	Pause();
	SetViewPointCenter(_mSonic->getPosition(), true);
	_diabox->UpdateString("Oops. Let's try again!");
}


void TurtorialScene::Pause()
{
	//_mSonic->SetVelocity(0,0);
	//_isPause = true;
	//_diabox->setVisible(true);
	//_diabox->setPosition(_mSonic->getPositionX(), _director->getWinSize().height*3/4);
	//blackImage->setPosition(_mSonic->getPosition());
	//blackImage->setVisible(true);
}

void TurtorialScene::Continue()
{
	//if (count_tuto == 12) //Bug fix: tap to continue can active button of frog
	//	_listMonster.at(0)->scheduleUpdate();
	//if(count_tuto!=7) //Bug fix: in Third button, player can break button before 
	//_myui->EnableAll();
	//if (count_tuto != 10) //Bug fix: When try again, it skip ring instruction
	//count_tuto++;
	//_isPause = false;
	//_mSonic->SetVelocityX(340);
	//_diabox->setVisible(false);
	//blackImage->setVisible(false);
}




bool TurtorialScene::onContactBegin(cocos2d::PhysicsContact & contact)
{
	auto spriteA = (Sprite*)contact.getShapeA()->getBody()->getNode(); // 1
	auto spriteB = (Sprite*)contact.getShapeB()->getBody()->getNode(); // 2

	int tagA = spriteA->getTag();                                      // 3
	int tagB = spriteB->getTag();

	if (tagA == Define::Player || tagB == Define::Player)
	{
		
		if (tagA == Define::Player)
		{
			
			Sonic *sonic = (Sonic*)spriteA;
			sonic->HandleCollision(spriteB);
		}
		else
		{
			
			Sonic *sonic = (Sonic*)spriteB;
			sonic->HandleCollision(spriteA);
		}
	}
	if (tagA == Define::LANDMONSTER || tagB == Define::LANDMONSTER)
	{
		if (tagA == Define::LANDMONSTER)
		{
			Monster *monster = (Monster*)spriteA;
			monster->HandleCollision(spriteB);
		}
		else
		{
			Monster *monster = (Monster*)spriteB;
			monster->HandleCollision(spriteA);
		}
	}

	return true;
}

void TurtorialScene::update(float dt)
{
	if (_mSonic->isDelete)
	Director::getInstance()->replaceScene(this->createScene());
	LevelScene::update(dt);
	
	{
		//if(_myui!=nullptr && _myui->_istouch) //Bug fix: tap button cant skip
		//	if (_isPause && count_tuto != 2 && count_tuto != 3 && count_tuto != 6 && count_tuto != 8) Continue();

		//if (_listButton.at(0)->getPositionX()- _mSonic->getPositionX() <= 800 && count_tuto < 2 && !_isPause)
		//{
		//	Tutorial1();
		//}

		//if (_listButton.at(0)->getPositionX() - _mSonic->getPositionX() <= 600 && count_tuto == 2 )
		//{
		//	Tutorial2();
		//	//count_tuto++;
		//}
		//if (count_tuto == 3 && !_isPause)
		//{
		//	Tutorial2_part1();
		//	
		//}
		//if (count_tuto == 4 && _isPause)
		//{
		//	if (_listButton.at(0)->isTrue)
		//	{
		//	Continue();
		//	_myui->EnableAll();
		//	}
		//	/*Pause();
		//	_diabox->UpdateString("Good job! Let's continue!");
		//	_diabox->SetTapToContinue(true);*/
		//}
		//if (_listButton.at(1)->getPositionX() - _mSonic->getPositionX() <= 150 && count_tuto ==5 && !_isPause)
		//{
		//	Tutorial3();
		//
		//	count_tuto++;
		//}
		//if (count_tuto == 6)
		//{
		//
		//	if (_listButton.at(1)->isDelete)
		//	{
		//		Continue();
		//	}
		//}
		//if (count_tuto == 7 && _listButton.at(2)->getPositionX()-_mSonic->getPositionX()<=650 && !_isPause)
		//{
		//
		//	if(!_isPause)
		//	Tutorial4();
		//}
		//if (count_tuto == 8)
		//{
		//	
		//	
		//	
		//		_myui->DisableExcept(_listButton.at(2)->mTag);
		//		_diabox->UpdateString("Press!!");
		//		_diabox->SetTapToContinue(false);
		//		Pause();
		//	if (_listButton.at(2)->isDelete)
		//		Continue();
		//}
		//if (count_tuto == 9 && _listButton.at(3)->getPositionX()-_mSonic->getPositionX()<=1200 && !_isPause)
		//{
		//	_diabox->UpdateString("OK! Now you know how to tap the screen!");
		//	_diabox->SetTapToContinue(true);
		//	Pause();
		//}
		///*if (count_tuto == 10 && _listRing.at(0)->getPositionX() - _mSonic->getPositionX()<=800 && !_isPause)
		//{
		//	Pause();
		//	_diabox->UpdateString("Collect ring to upgrade your abilities");
		//	count_tuto++;
		//}*/
		//if (count_tuto == 12 && _listMonster.at(0)->getPositionX() - _mSonic->getPositionX() <= 800 && !_isPause)
		//{
		//	Pause();
		//	_listMonster.at(0)->unscheduleUpdate();
		//	_diabox->UpdateString("Be careful! If you let button break, \nyou'll hit the enemy and drop your rings");
		//}
	}
	/*if (_isPause)
	{
		count_to_move_scene++;
		_mSonic->SetVelocityX(0);
		auto pos_scene = this->getPosition();
		auto sonic_pos = _mSonic->getPosition();
		this->setPosition((Vec2(delta_x,0)*_director->getDeltaTime() + pos_scene));
		

		if (count_to_move_scene == 120)
		{
			count_to_move_scene = 0;
			delta_x *= -1;
		}
	}
	else
	{
		if (_mSonic->getPosition().x < 0) _mSonic->setPosition(0, _mSonic->getPosition().y);*/
		

	//}

}



bool TurtorialScene::init()
{
	LevelScene::init();
	

	LoadMap("LevelScene/StoneMap/tutorial.tmx");
	
	_diabox = new MyDialogBox();
	_diabox->setPosition(1000, 400);
	_diabox->SetScale(0.7);
	_diabox->SetTapToContinue(true);

	this->addChild(_diabox, 7);

	//_mSonic->setPosition(1000, 200);

	
	/*blackImage = Sprite::create("TurtorialScene/black.png");
	blackImage->setColor(Color3B(0, 0, 0));
	blackImage->setScale(20);
	blackImage->setOpacity(100);
	this->addChild(blackImage, 6);*/
	
	_mSonic->setPosition(300, 150);
	SetViewPointCenter(_mSonic->getPosition(), true);
	_mSonic->setZOrder(7);



	
	//Listener
	{
		auto listener1 = EventListenerTouchOneByOne::create();

		listener1->onTouchBegan = [this](Touch* touch, Event* event) {
		
			return true;
		};

		// trigger when you let up
		listener1->onTouchEnded = [this](Touch* touch, Event* event) {
		//	if (_isPause  && count_tuto != 6 && count_tuto != 8) Continue();
		};


		_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, this);




		auto contactListener = EventListenerPhysicsContact::create();
		contactListener->onContactBegin = CC_CALLBACK_1(TurtorialScene::onContactBegin, this);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
		scheduleOnce(CC_SCHEDULE_SELECTOR(TurtorialScene::updateStart), 0);


	}

	
	return true;
}

