#include "TestScene.h"



TestScene::TestScene()
{
}


TestScene::~TestScene()
{
}

void TestScene::LoadSound()
{
	audio = SimpleAudioEngine::getInstance();
	audio->preloadBackgroundMusic(Define::_music_lv1_background_path);
	audio->playBackgroundMusic(Define::_music_lv1_background_path);
	audio->preloadEffect(Define::_music_combo_effect_path);
	audio->preloadEffect(Define::_music_eat_ring_efftect_path);
	audio->preloadEffect(Define::_music_roll_effect_path);
	audio->preloadEffect(Define::_music_jump_effect_path);
	audio->preloadEffect(Define::_music_eat_ring_efftect_path_1);
	audio->preloadEffect(Define::_music_button_effect_path);

	//SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.1f);
	//SimpleAudioEngine::getInstance()->setEffectsVolume(0.1f);
	//audio->preloadBackgroundMusic("stdioBackGroungGamePlay.mp3");

	// sound effect.
	//audio->preloadEffect("stdioEffeectShot.wav");
	//audio->preloadEffect("stdioEffectCollision.wav");

	// khi không cần sử dụng đoạn nhạc nào đó trong trò chơi.
	
}

void TestScene::RollBackground()
{
	_backgroundNode->setPosition(_backgroundNode->getPosition() - Vec2(5, 0));
	_backgroundNode->updatePosition();
	_backgroundNode2->setPosition(_backgroundNode2->getPosition() - Vec2(5, 0));
	_backgroundNode2->updatePosition();
}


void TestScene::CheckButton()
{
	if(!_mSonic->isInMultipleButton)
	for (int i = _listButton.size() - 2; i > -1; i--)
	{		
		if (_listButton.at(i)->isDelete /*&& _listButton.at(i+1)->getPositionX() - _mSonic->getPositionX() < 600*/)
		{
			_listButton.at(i + 1)->SetCanActive(true);
			break;
		}
	}

	for (auto mon : _listMonster)
	{
		MultipleButton* multi_but = mon->_multiButton;
		bool canActive = true;
		for (auto tap_button : _listButton)
		{
			if (tap_button->getPositionX() < multi_but->getPositionX() && !tap_button->isDelete)
			{
				canActive = false;
				break;
			}
		}
		multi_but->canActive = canActive;
	}

	
	
}

void TestScene::LoadMap(CCTMXTiledMap * map)
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


			auto boundBody = PhysicsBody::createBox(Size(wi_box, he_box), PhysicsMaterial(0.1f, 1.0f, 0.0f));
			boundBody->setDynamic(false);


			boundBody->setCategoryBitmask(2);
			boundBody->setCollisionBitmask(25);
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


			auto button = new TapButton(Vec2(x_box, y_box), _mSonic, this);
			button->setZOrder(8);
			button->canActive = false;
			_listButton.push_back(button);
		}
		
		for (int i = 0; i < _listButton.size(); i++)
		{
			for (int j = i + 1; j < _listButton.size(); j++)
			{
				if (_listButton.at(i)->getPositionX() > _listButton.at(j)->getPositionX())
				{
					auto temp = _listButton.at(i);
					_listButton.at(i) = _listButton.at(j);
					_listButton.at(j) = temp;
				}
			}
		}
		_listButton.at(0)->SetCanActive(true);
	

		////Load Monster Position
		TMXObjectGroup *objectGroup_monster = _tileMap->getObjectGroup("Monster");
		for (int i = 0; i < objectGroup_monster->getObjects().size(); i++)
		{

			Value objectemp = objectGroup_monster->getObjects().at(i);

			float wi_box = objectemp.asValueMap().at("width").asFloat();
			float he_box = objectemp.asValueMap().at("height").asFloat();
			float x_box = objectemp.asValueMap().at("x").asFloat() + wi_box / 2;
			float y_box = objectemp.asValueMap().at("y").asFloat() + he_box / 2;

			Monster *mon = new FrogMonster(_mSonic);
			mon->setPosition(x_box, y_box);
			_listMonster.pushBack(mon);
			this->addChild(mon, 7);
			}

		//Load MushRoom
		TMXObjectGroup *objectGroup_Mushroom = _tileMap->getObjectGroup("Mushroom");
		for (int i = 0; i < objectGroup_Mushroom->getObjects().size(); i++)
		{

			Value objectemp = objectGroup_Mushroom->getObjects().at(i);

			float wi_box = objectemp.asValueMap().at("width").asFloat();
			float he_box = objectemp.asValueMap().at("height").asFloat();
			float x_box = objectemp.asValueMap().at("x").asFloat() + wi_box / 2;
			float y_box = objectemp.asValueMap().at("y").asFloat() + he_box / 2;

			Mushroom *mush = new Mushroom();
			mush->setPosition(x_box, y_box);
			this->addChild(mush, 7);
		}

		//// Process object layer 
		auto objectGroup = map->getObjectGroup("Land2");
		auto objects = objectGroup->getObjects();
		for (auto object : objects)
		{
			auto dic = object.asValueMap();
			float objectX = dic.at("x").asFloat();
			float objectY = dic.at("y").asFloat();


			auto drawNode = DrawNode::create();
			auto pointsVector = dic.at("polylinePoints").asValueVector();
			auto size = pointsVector.size();
			// Get Point 
			if (size > 0)
			{
				Vec2* points = new Vec2[size];
				int i = 0;
				for (auto pointValue : pointsVector)
				{
					auto dicp = pointValue.asValueMap();
					auto x = dicp.at("x").asFloat();
					auto y = -dicp.at("y").asFloat(); // y takes a negative value 
					points[i] = Vec2(x, y);
					i++;
				}
				// Draw the polyline 
				//  drawNode->drawPoly(points, size, false, Color4F::RED);
				auto sprite = Sprite::create();
				auto box = PhysicsBody::createEdgePolygon(points, 5);
				sprite->setPhysicsBody(box);
				sprite->setPosition(objectX, objectY);
				this->addChild(sprite);
				delete[] points;
				//drawNode->setPosition(objectX, objectY);
				//this->addChild(drawNode, 10);
			}
		}






	}
	catch (...) {};
}

void TestScene::SetViewPointCenter(Point position, bool isFast)
{
	Size winSize = _director->getWinSize();

	int x = MAX(position.x, winSize.width / 2);
	int y = MAX(position.y, winSize.height / 2);
	x = MIN(x, (_tileMap->getMapSize().width * this->_tileMap->getTileSize().width) - winSize.width / 2);
	y = MIN(y, (_tileMap->getMapSize().height * _tileMap->getTileSize().height) - winSize.height / 2);
	Vec2 actualPosition = Vec2(x, y);

	Vec2 centerOfView = Vec2(winSize.width / 2, winSize.height / 2);
	Vec2 viewPoint;

	if (_mSonic->getPositionX()<13500)
		viewPoint = centerOfView - actualPosition + Vec2(-300, 0);
	else
		viewPoint = centerOfView - actualPosition;


	auto currentCameraPosition = this->getPosition();
	//	this->getScene()->getDefaultCamera()->setPosition(viewPoint);
	if (isFast)
		this->setPosition(viewPoint);
	else
		this->setPosition((viewPoint - currentCameraPosition)*_director->getDeltaTime() + currentCameraPosition);
}

bool TestScene::onContactBegin(cocos2d::PhysicsContact & contact)
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

void TestScene::update(float dt)
{
	log("%f", _mSonic->GetVelocity().x);
	//CCLog(to_string().c_str());
	//for (int i = 0; i < 3; ++i)
	//{
	//	this->getScene()->getPhysicsWorld()->step(1 / 60.0f);
	//}

	if (_mSonic->isDelete)
		Director::getInstance()->replaceScene(this->createScene());

	RollBackground();
	if (_mSonic->getPosition().x < 0) _mSonic->setPosition(0, _mSonic->getPosition().y);
	SetViewPointCenter(_mSonic->getPosition(), true);
	CheckButton();

	

}

void TestScene::updateStart(float dt)
{
	//this->getScene()->getPhysicsWorld()->setFixedUpdateRate(60);
	_myui = new MyUI(_mSonic);

	this->getScene()->addChild(_myui);
	_myui->setVisible(true);

}



bool TestScene::init()
{
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
	_tileMap->initWithTMXFile("LevelScene/LV1/untitled.tmx");
	//_tileMap->initWithTMXFile("TurtorialScene/untitled.tmx");
	this->addChild(_tileMap);


	//Add Sonic
	_mSonic = new Sonic();
	_mSonic->setPosition(500, 150);
	SetViewPointCenter(_mSonic->getPosition(), true);
	this->addChild(_mSonic);
	LoadMap(_tileMap);




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

	_mSonic->setZOrder(7);

	LoadSound();
	MyParticle::CreateWind(_mSonic->getPosition(), this);

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(TestScene::onContactBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

	scheduleOnce(CC_SCHEDULE_SELECTOR(TestScene::updateStart), 0);


	this->scheduleUpdate();
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
