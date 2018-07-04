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
	_diabox->UpdateString("Look! There is a symbol like \none of four symbols on your left\nscreen");
	//_listLabel.at(1)->setString("Look! There is a symbol like one of four symbols on your left screen\n(tap screen to continue)");


}

void TurtorialScene::Tutorial2()
{
	_diabox->UpdateString("The white circle will shrink to the symbol\nWhen it fits, press the suitable button on left screen\n or else the button will break, Sonic does nothing");
	_diabox->SetTapToContinue(false);
	Pause();
	_listButton.at(0)->circle->runAction(Sequence::create(ScaleTo::create(1.5, 0.29), CallFuncN::create(CC_CALLBACK_0(TurtorialScene::Tutorial2_part1, this)),NULL));

	
}

void TurtorialScene::Tutorial2_part1()
{

	auto fadeOut = FadeOut::create(0.1f);
	auto reverse = fadeOut->reverse();
	ActionInterval *fade = Sequence::create(fadeOut, reverse, nullptr);
	auto fading = RepeatForever::create(fade);
	_listButton.at(0)->runAction(fading);
	_myui->DisableExcept(_listButton.at(0)->mTag);

	_listButton.at(0)->scheduleUpdate();
	_listButton.at(0)->can_Active = true;
	_listButton.at(0)->time_dissapear = 1000;
	_listButton.at(0)->isFirst = true;



}

void TurtorialScene::Tutorial3()
{
	Pause();
	_diabox->UpdateString("Wait...");
	_diabox->SetTapToContinue(false);

	_myui->DisableExcept(_listButton.at(1)->mTag);
	_listButton.at(1)->unscheduleUpdate();
	_listButton.at(1)->circle->runAction(Sequence::create(ScaleTo::create(1.5, 0.29), CallFuncN::create(CC_CALLBACK_0(TurtorialScene::Tutorial3_part1, this)), NULL));
}

void TurtorialScene::Tutorial3_part1()
{
	_diabox->UpdateString("Press now!!!!");
	_diabox->SetTapToContinue(false);
	
	_listButton.at(1)->time_dissapear = 1000;
	_listButton.at(1)->scheduleUpdate();
	_listButton.at(1)->Dissapear();
	_listButton.at(1)->can_Active = true;
}

void TurtorialScene::Tutorial4()
{
	_diabox->UpdateString("Good! Let's try another one!");
	_diabox->SetTapToContinue(true);
	_listButton.at(2)->time_dissapear = 1000;
	Pause();
}
void TurtorialScene::ResetTutorial4()
{
	_mSonic->setPosition(5000, 300);
	TapButton *tap= new TapButton(1, _listButton.at(3)->getPosition(), _mSonic, this);
	tap->isFirst = true;
	_listButton.erase(_listButton.begin() + 3);
	_listButton.insert(3, tap);
	Pause();
	SetViewPointCenter(_mSonic->getPosition(),true);
	_diabox->UpdateString("Oops. Let's try again!");
}

void TurtorialScene::RollBackground()
{
	_backgroundNode->setPosition(_backgroundNode->getPosition() - Vec2(5, 0));
	_backgroundNode->updatePosition();
	_backgroundNode2->setPosition(_backgroundNode2->getPosition() - Vec2(5, 0));
	_backgroundNode2->updatePosition();

}

void TurtorialScene::Pause()
{
	_isPause = true;
	_diabox->setVisible(true);
	_diabox->setPosition(_mSonic->getPositionX(), 500);
	blackImage->setPosition(_mSonic->getPosition());
	blackImage->setVisible(true);
}

void TurtorialScene::Continue()
{
	_myui->EnableAll();
	if (count_tuto != 10) //Bug fix: When try again, it skip ring instruction
	count_tuto++;
	_isPause = false;
	_mSonic->SetVelocityX(340);
	_diabox->setVisible(false);
	blackImage->setVisible(false);
}

void TurtorialScene::LoadMap(CCTMXTiledMap * map)
{
	try
	{
		//Load Land
		TMXObjectGroup *objectGroup_land = _tileMap->getObjectGroup("Land");
		for (int i = 0; i < objectGroup_land->getObjects().size(); i++)
		{

			Value objectemp = objectGroup_land->getObjects().at(i);

			float wi_box = objectemp.asValueMap().at("width").asFloat();
			float he_box = objectemp.asValueMap().at("height").asFloat();
			float x_box = objectemp.asValueMap().at("x").asFloat() + wi_box / 2;
			float y_box = objectemp.asValueMap().at("y").asFloat() + he_box / 2;

			auto edgeSp = Sprite::create();
			edgeSp->setTag(Define::land);


			auto boundBody = PhysicsBody::createBox(Size(wi_box, he_box), PhysicsMaterial(0.1f, 0.0f, 0.0f));
			boundBody->setDynamic(false);


			boundBody->setCategoryBitmask(2);
			boundBody->setCollisionBitmask(17);
			boundBody->setContactTestBitmask(1);

			edgeSp->setPhysicsBody(boundBody);
			edgeSp->setPosition(Vec2(x_box, y_box));

			this->addChild(edgeSp); // Add v�o Layer
		}



		//Load DieLand (die when collision with)
		TMXObjectGroup *objectGroup_hold_land = _tileMap->getObjectGroup("DieLand");
		for (int i = 0; i < objectGroup_hold_land->getObjects().size(); i++)
		{

			Value objectemp = objectGroup_hold_land->getObjects().at(i);

			float wi_box = objectemp.asValueMap().at("width").asFloat();
			float he_box = objectemp.asValueMap().at("height").asFloat();
			float x_box = objectemp.asValueMap().at("x").asFloat() + wi_box / 2;
			float y_box = objectemp.asValueMap().at("y").asFloat() + he_box / 2;

			auto edgeSp = Sprite::create();
			edgeSp->setTag(Define::DIELAND);
			auto boundBody = PhysicsBody::createBox(Size(wi_box, he_box));
			boundBody->getShape(0)->setFriction(10.0f);
			boundBody->setDynamic(false);
			boundBody->getShape(0)->setRestitution(100.0f);


			boundBody->setCategoryBitmask(4);
			boundBody->setCollisionBitmask(1);
			boundBody->setContactTestBitmask(1);



			edgeSp->setPhysicsBody(boundBody);
			edgeSp->setPosition(Vec2(x_box, y_box));

			this->addChild(edgeSp); // Add vao Layer
		}

		//Load Ring Position
		TMXObjectGroup *objectGroup_ring = _tileMap->getObjectGroup("Ring");
		for (int i = 0; i < objectGroup_ring->getObjects().size(); i++)
		{

			Value objectemp = objectGroup_ring->getObjects().at(i);

			float wi_box = objectemp.asValueMap().at("width").asFloat();
			float he_box = objectemp.asValueMap().at("height").asFloat();
			float x_box = objectemp.asValueMap().at("x").asFloat() + wi_box / 2;
			float y_box = objectemp.asValueMap().at("y").asFloat() + he_box / 2;

			auto ring = new SmallRing();
			ring->setPosition(x_box, y_box);
			_listRing.pushBack(ring);
			this->addChild(ring);
		}

		//Load Button Position
		TMXObjectGroup *objectGroup_button = _tileMap->getObjectGroup("Button");
		for (int i = 0; i < objectGroup_button->getObjects().size(); i++)
		{

			Value objectemp = objectGroup_button->getObjects().at(i);

			float wi_box = objectemp.asValueMap().at("width").asFloat();
			float he_box = objectemp.asValueMap().at("height").asFloat();
			float x_box = objectemp.asValueMap().at("x").asFloat() + wi_box / 2;
			float y_box = objectemp.asValueMap().at("y").asFloat() + he_box / 2;

			int a = RandomHelper::random_int(1, 4);
			auto button = new TapButton(a, Vec2(x_box, y_box), _mSonic, this);
			button->setZOrder(8);
			button->circle->setZOrder(7);
			button->isFirst = true;
			_listButton.pushBack(button);
		}
		_listButton.at(0)->unscheduleUpdate();
		_listButton.at(1)->unscheduleUpdate();

		//Load Text Position
		TMXObjectGroup *objectGroup_text = _tileMap->getObjectGroup("Text");
		for (int i = 0; i < objectGroup_text->getObjects().size(); i++)
		{

			Value objectemp = objectGroup_text->getObjects().at(i);

			float wi_box = objectemp.asValueMap().at("width").asFloat();
			float he_box = objectemp.asValueMap().at("height").asFloat();
			float x_box = objectemp.asValueMap().at("x").asFloat() + wi_box / 2;
			float y_box = objectemp.asValueMap().at("y").asFloat() + he_box / 2;

			Label* myLabel = Label::createWithTTF("", "fonts/times.ttf", 24);
			myLabel->setPosition(x_box, y_box);
			this->addChild(myLabel, 7);
			_listLabel.pushBack(myLabel);
		}

		////Load Monster Position
		TMXObjectGroup *objectGroup_monster = _tileMap->getObjectGroup("Monster");
		for (int i = 0; i < objectGroup_monster->getObjects().size(); i++)
		{

			Value objectemp = objectGroup_monster->getObjects().at(i);

			float wi_box = objectemp.asValueMap().at("width").asFloat();
			float he_box = objectemp.asValueMap().at("height").asFloat();
			float x_box = objectemp.asValueMap().at("x").asFloat() + wi_box / 2;
			float y_box = objectemp.asValueMap().at("y").asFloat() + he_box / 2;

			Monster *mon = new Monster();
			mon->setPosition(x_box, y_box);
			this->addChild(mon, 7);
			_listMonster.pushBack(mon);
		}

			//// Process object layer 
			//auto objectGroup = map->getObjectGroup("Land2");
			//auto objects = objectGroup->getObjects();
			//for (auto object : objects)
			//{
			//	auto dic = object.asValueMap();
			//	float objectX = dic.at("x").asFloat();
			//	float objectY = dic.at("y").asFloat();


			//	auto drawNode = DrawNode::create();
			//	auto pointsVector = dic.at("polylinePoints").asValueVector();
			//	auto size = pointsVector.size();
			//	// Get Point 
			//	if (size > 0)
			//	{
			//		Vec2* points = new Vec2[size];
			//		int i = 0;
			//		for (auto pointValue : pointsVector)
			//		{
			//			auto dicp = pointValue.asValueMap();
			//			auto x = dicp.at("x").asFloat();
			//			auto y = -dicp.at("y").asFloat(); // y takes a negative value 
			//			points[i] = Vec2(x, y);
			//			i++;
			//		}
			//		// Draw the polyline 
			//		//  drawNode->drawPoly(points, size, false, Color4F::RED);
			//		auto sprite = Sprite::create();
			//		auto box = PhysicsBody::createEdgePolygon(points, 5);
			//		sprite->setPhysicsBody(box);
			//		sprite->setPosition(objectX, objectY);
			//		this->addChild(sprite);
			//		delete[] points;
			//		//drawNode->setPosition(objectX, objectY);
			//		//this->addChild(drawNode, 10);
			//	}
			//}

	




	}
	catch (...) {};


}

void TurtorialScene::SetViewPointCenter(Point position,bool isFast)
{
	Size winSize = _director->getWinSize();

	int x = MAX(position.x, winSize.width / 2);
	int y = MAX(position.y, winSize.height / 2);
	x = MIN(x, (_tileMap->getMapSize().width * this->_tileMap->getTileSize().width) - winSize.width / 2);
	y = MIN(y, (_tileMap->getMapSize().height * _tileMap->getTileSize().height) - winSize.height / 2);
	Vec2 actualPosition = Vec2(x, y);

	Vec2 centerOfView = Vec2(winSize.width / 2, winSize.height / 2);
	Vec2 viewPoint = centerOfView - actualPosition + Vec2(-400, 0);

	auto currentCameraPosition = this->getPosition();
	if(isFast)
	this->setPosition(viewPoint);
	else
	this->setPosition((viewPoint - currentCameraPosition)*_director->getDeltaTime() + currentCameraPosition);
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
			if (spriteB->getTag() == Define::DIELAND)
				ResetTutorial4();
			Sonic *sonic = (Sonic*)spriteA;
			sonic->HandleCollision(spriteB);
		}
		else
		{
			if (spriteA->getTag() == Define::DIELAND)
				ResetTutorial4();
			Sonic *sonic = (Sonic*)spriteB;
			sonic->HandleCollision(spriteA);
		}
	}
	if (tagA == Define::LANDMONSTER || tagB == Define::LANDMONSTER)
	{
		
	/*	auto ring = new SmallRing();
		ring->setPosition(_mSonic->getPosition());
		this->addChild(ring);*/


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
	


	if (_listButton.at(0)->getPositionX()- _mSonic->getPositionX() <= 150 && count_tuto < 2 && !_isPause)
	{
		Tutorial1();
	}
	if (count_tuto == 2 )
	{
		Tutorial2();
		count_tuto++;
	}
	if (count_tuto == 3 )
	{
		if (_listButton.at(0)->isDelete)
		{
			Continue();
			_myui->EnableAll();
		}
	}
	if (count_tuto == 4 && _listButton.at(1)->getPositionX() - _mSonic->getPositionX() <= 900 && !_isPause)
	{
		Pause();
		_diabox->UpdateString("Good job! Let's continue!");
		_diabox->SetTapToContinue(true);
	}
	if (_listButton.at(1)->getPositionX() - _mSonic->getPositionX() <= 150 && count_tuto ==5 && !_isPause)
	{
		Tutorial3();
		count_tuto++;
	}
	if (count_tuto == 6)
	{

		if (_listButton.at(1)->isDelete)
		{
			Continue();
		}
	}
	if (count_tuto == 7 && _listButton.at(2)->getPositionX()-_mSonic->getPositionX()<=650 && !_isPause)
	{
	
		if(!_isPause)
		Tutorial4();
	}
	if (count_tuto == 8)
	{
		
		
		if (_listButton.at(2)->can_Active)
		{
			_myui->DisableExcept(_listButton.at(2)->mTag);
			_diabox->UpdateString("Press!!");
			_diabox->SetTapToContinue(false);
			Pause();
		}
		if (_listButton.at(2)->isDelete)
			Continue();
	}
	if (count_tuto == 9 && _listButton.at(3)->getPositionX()-_mSonic->getPositionX()<=1200 && !_isPause)
	{
		_diabox->UpdateString("OK! Now you know how to press the button!");
		_diabox->SetTapToContinue(true);
		Pause();
	}
	if (count_tuto == 10 && _listRing.at(0)->getPositionX() - _mSonic->getPositionX()<=800 && !_isPause)
	{
		Pause();
		_diabox->UpdateString("Collect ring to upgrade your abilities");
		count_tuto++;
	}
	if (count_tuto == 12 && _listMonster.at(0)->getPositionX() - _mSonic->getPositionX() <= 800 && !_isPause)
	{
		Pause();
		_diabox->UpdateString("Be careful! If you let button break, \nyou'll hit the enemy and drop your rings");
	}
	RollBackground();
	if (_isPause)
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
		if (_mSonic->getPosition().x < 0) _mSonic->setPosition(0, _mSonic->getPosition().y);
		SetViewPointCenter(_mSonic->getPosition(),true);

	}

}

void TurtorialScene::updateStart(float dt)
{
	_myui = new MyUI(_mSonic);

	this->getScene()->addChild(_myui);
	_myui->setVisible(false);

	
}

bool TurtorialScene::init()
{
	//init- getSize
	if (!Layer::init())
	{
		return false;
	}
	srand(time(NULL));
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	Size winSize = Director::getInstance()->getWinSize();



	//Add MAP
	_tileMap = new TMXTiledMap();
	_tileMap->initWithTMXFile("TurtorialScene/untitled.tmx");
	this->addChild(_tileMap);


	//Add Sonic
	_mSonic = new Sonic();
	_mSonic->setPosition(500, 200);
	SetViewPointCenter(_mSonic->getPosition(),true);
	this->addChild(_mSonic);
	LoadMap(_tileMap);
	

	_diabox = new MyDialogBox();
	_diabox->setPosition(1000, 400);
	_diabox->SetScale(0.7);
	_diabox->SetTapToContinue(true);

	this->addChild(_diabox, 7);


	//Monster* a = new Monster();
	//a->setPosition(2000, 200);
	//this->addChild(a);


	//2 Parallax Scrolling
	{
		_backgroundNode = InfiniteParallaxNode::create();

		auto _galaxy = Sprite::create("Map_stone/stone_bg3.png");
		_galaxy->setAnchorPoint(Point(0, 0));
		_galaxy->setScale(visibleSize.width / _galaxy->getContentSize().width); //auto scale background fitting screen
		_backgroundNode->addChild(_galaxy, -1, Point(0.1, 1), Point(0, 0));
		this->addChild(_backgroundNode, -1);

		_backgroundNode2 = InfiniteParallaxNode::create();

		auto _galaxy2 = Sprite::create("Map_stone/stone_bg3.png");
		_galaxy2->setAnchorPoint(Point(0, 0));
		_galaxy2->setScale(visibleSize.width / _galaxy->getContentSize().width); //auto scale background fitting screen
		_backgroundNode2->addChild(_galaxy2, -1, Point(0.1, 1), Point(_galaxy2->getContentSize().width * _galaxy->getScale(), 0));
		this->addChild(_backgroundNode2, -1);

	}
	blackImage = Sprite::create("TurtorialScene/black.png");
	blackImage->setColor(Color3B(0, 0, 0));
	blackImage->setScale(20);
	blackImage->setOpacity(100);
	this->addChild(blackImage, 6);

	_mSonic->setZOrder(7);


	
	//Listener
	{
		auto listener1 = EventListenerTouchOneByOne::create();

		listener1->onTouchBegan = [this](Touch* touch, Event* event) {
			start_touch_position = touch->getLocation();
			return true;
		};

		// trigger when you let up
		listener1->onTouchEnded = [this](Touch* touch, Event* event) {
			end_touch_position = touch->getLocation();
			_mSonic->handle_swipe(start_touch_position, end_touch_position);
			if (_isPause && count_tuto != 2 && count_tuto != 3 && count_tuto != 6 && count_tuto != 8) Continue();
		};


		_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, this);




		auto contactListener = EventListenerPhysicsContact::create();
		contactListener->onContactBegin = CC_CALLBACK_1(TurtorialScene::onContactBegin, this);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
		scheduleOnce(CC_SCHEDULE_SELECTOR(TurtorialScene::updateStart), 0);


	}

	this->scheduleUpdate();
	Pause();
	return true;
}

