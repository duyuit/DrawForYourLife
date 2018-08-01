#include "LevelScene.h"



LevelScene::LevelScene()
{
}


LevelScene::~LevelScene()
{


}

void LevelScene::MyPause()
{
	// Pause everthing
	this->pause();
	for (auto child : this->getChildren()) {
		child->pauseSchedulerAndActions();
	}
	Director::getInstance()->getRunningScene()->getPhysicsWorld()->setSpeed(0);
}
void LevelScene::MyResume()
{
	// Pause everthing
	this->resume();
	for (auto child : this->getChildren()) {
		child->resumeSchedulerAndActions();
	}
	Director::getInstance()->getRunningScene()->getPhysicsWorld()->setSpeed(1);
}

void LevelScene::ReloadScene()
{
}

void LevelScene::NextScene()
{
}

void LevelScene::SortButton()
{
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
}

void LevelScene::LoadSound()
{
	audio = SimpleAudioEngine::getInstance();
	audio->preloadBackgroundMusic(Define::_music_lv1_background_path);
	audio->playBackgroundMusic(Define::_music_lv1_background_path, true);
	audio->preloadEffect(Define::_music_combo_effect_path);
	audio->preloadEffect(Define::_music_eat_ring_efftect_path);
	audio->preloadEffect(Define::_music_roll_effect_path);
	audio->preloadEffect(Define::_music_jump_effect_path);
	audio->preloadEffect(Define::_music_button_effect_path);
	audio->preloadEffect(Define::_music_finish_level_path);
}

void LevelScene::CreateParallaxNode(string path)
{
	//2 Parallax Scrolling
	{
		_backgroundNode = InfiniteParallaxNode::create();

		auto _galaxy = Sprite::create(path);
		_galaxy->setAnchorPoint(Point(0, 0));
		_galaxy->setScale(_director->getVisibleSize().width / _galaxy->getContentSize().width); //auto scale background fitting screen
		_backgroundNode->addChild(_galaxy, -1, Point(0.1, 1), Point(0, 0));
		this->addChild(_backgroundNode, -100);

		_backgroundNode2 = InfiniteParallaxNode::create();

		auto _galaxy2 = Sprite::create(path);
		_galaxy2->setAnchorPoint(Point(0, 0));
		_galaxy2->setScale(_director->getVisibleSize().width / _galaxy->getContentSize().width); //auto scale background fitting screen
		_backgroundNode2->addChild(_galaxy2, -1, Point(0.1, 1), Point(_galaxy2->getContentSize().width * _galaxy->getScale(), 0));
		this->addChild(_backgroundNode2, -100);
	}
}

void LevelScene::CreateTileLayer(string path)
{
	Sprite* layer = Sprite::create(path + "1.png");
	layer->setAnchorPoint(Vec2(0, 0));
	layer->setPosition(0, 0);
	this->addChild(layer, -1);

	Sprite* layer2 = Sprite::create(path + "2.png");
	layer2->setAnchorPoint(Vec2(0, 0));
	layer2->setPosition(layer->getContentSize().width, 0);
	this->addChild(layer2, -1);
}

void LevelScene::RollBackground()
{
	_backgroundNode->setPosition(_backgroundNode->getPosition() - Vec2(5 * _speedParallax, 0));
	_backgroundNode->updatePosition();
	_backgroundNode2->setPosition(_backgroundNode2->getPosition() - Vec2(5 * _speedParallax, 0));
	_backgroundNode2->updatePosition();

	
}

void LevelScene::CheckButton()
{
	if (!_mSonic->isInMultipleButton)
		for (int i = _listButton.size() - 2; i > -1; i--)
		{
			if (_listButton.at(i)->isDelete && _listButton.at(i+1)->getPositionX() - _mSonic->getPositionX() < 600)
			{
				_listButton.at(i + 1)->SetCanActive(true);
				break;
			}
		}

	for (auto multi_button : _listMultipleButton)
	{
		
		bool canActive = true;
		for (auto tap_button : _listButton)
		{
			if (tap_button->getPositionX() < multi_button->getPositionX() && !tap_button->isDelete)
			{
				canActive = false;
				break;
			}
		}
		multi_button->canActive = canActive;
	}
}

void LevelScene::LoadMap(string path)
{
	//Add MAP
	_tileMap = new TMXTiledMap();
	_tileMap->initWithTMXFile(path);
	this->addChild(_tileMap);

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

		TMXObjectGroup *objectGroup_fish = _tileMap->getObjectGroup("Fish");
		for (int i = 0; i < objectGroup_fish->getObjects().size(); i++)
		{

			Value objectemp = objectGroup_fish->getObjects().at(i);

			float wi_box = objectemp.asValueMap().at("width").asFloat();
			float he_box = objectemp.asValueMap().at("height").asFloat();
			float x_box = objectemp.asValueMap().at("x").asFloat() + wi_box / 2;
			float y_box = objectemp.asValueMap().at("y").asFloat() + he_box / 2;

			SharkMonster *mush = new SharkMonster(_mSonic,Vec2(x_box,y_box));
			_listButton.push_back(mush->_tapButton);
			this->addChild(mush, 7);
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
			_listMultipleButton.pushBack(mon->_multiButton);
			this->addChild(mon, 7);
		}
		SortButton();
		//Load Mushroom
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

		//Load Chest
		TMXObjectGroup *objectGroup_Chest = _tileMap->getObjectGroup("Chest");
		for (int i = 0; i < objectGroup_Chest->getObjects().size(); i++)
		{

			Value objectemp = objectGroup_Chest->getObjects().at(i);

			float wi_box = objectemp.asValueMap().at("width").asFloat();
			float he_box = objectemp.asValueMap().at("height").asFloat();
			float x_box = objectemp.asValueMap().at("x").asFloat() + wi_box / 2;
			float y_box = objectemp.asValueMap().at("y").asFloat() + he_box / 2;

			BonusChest *chest = new BonusChest(_mSonic);
			chest->setPosition(x_box, y_box);
			_listBonus.pushBack(chest);
			this->addChild(chest, 1);
			_listMultipleButton.pushBack(chest->_multiButton);
		}

		//Load finish flag
		TMXObjectGroup *objectGroup_finish = _tileMap->getObjectGroup("Finish");
		for (int i = 0; i < objectGroup_finish->getObjects().size(); i++)
		{

			Value objectemp = objectGroup_finish->getObjects().at(i);

			float wi_box = objectemp.asValueMap().at("width").asFloat();
			float he_box = objectemp.asValueMap().at("height").asFloat();
			float x_box = objectemp.asValueMap().at("x").asFloat() + wi_box / 2;
			float y_box = objectemp.asValueMap().at("y").asFloat() + he_box / 2;

			auto finish = new FinishFlag();

			finish->setPosition(x_box, y_box);
			this->addChild(finish, 1);
		}

		//// Process object layer 
		//auto objectGroup = _tileMap->getObjectGroup("Land2");
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

void LevelScene::SetViewPointCenter(Point position, bool isFast)
{
	if (_tileMap == nullptr) return;
	Size winSize = _director->getWinSize();

	int x = MAX(position.x, winSize.width / 2);
	int y = MAX(position.y, winSize.height / 2);
	x = MIN(x, (_tileMap->getMapSize().width * this->_tileMap->getTileSize().width) - winSize.width / 2);
	y = MIN(y, (_tileMap->getMapSize().height * _tileMap->getTileSize().height) - winSize.height / 2);
	Vec2 actualPosition = Vec2(x, y);

	Vec2 centerOfView = Vec2(winSize.width / 2, winSize.height / 2);
	Vec2 viewPoint;


	viewPoint = centerOfView - actualPosition + Vec2(-400, 0);
	//viewPoint = centerOfView - actualPosition + Vec2(-300, 0);
	auto currentCameraPosition = this->getPosition();

	/*if (_mSonic->mCurrentState->GetState() != SonicState::ROLL_CHEST)
	{*/
		//this->setPosition(viewPoint);
		this->setPosition((viewPoint - currentCameraPosition)*0.05 + currentCameraPosition);
	//}
}

bool LevelScene::onContactBegin(cocos2d::PhysicsContact & contact)
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

void LevelScene::update(float dt)
{
	/*for (int i = 0; i < 3; ++i)
	{
		this->getScene()->getPhysicsWorld()->step(1 / 60.0f);
	}*/


	RollBackground();
	if (_mSonic->scene_over)
		return;

	if (_mSonic->getPosition().x < 0) _mSonic->setPosition(0, _mSonic->getPosition().y);
	SetViewPointCenter(_mSonic->getPosition(), true);
	CheckButton();
}

void LevelScene::updateStart(float dt)
{
	this->getScene()->getPhysicsWorld()->setFixedUpdateRate(60);
	_myui = new MyUI(_mSonic);

	this->getScene()->addChild(_myui);
	_myui->setVisible(true);
}

bool LevelScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	srand(time(NULL));
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	Size winSize = Director::getInstance()->getWinSize();






	//Add Sonic
	_mSonic = new Sonic();
	_mSonic->setPosition(500, 200);
	SetViewPointCenter(_mSonic->getPosition(), true);
	this->addChild(_mSonic);

	_mSonic->setZOrder(7);

	LoadSound();


	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(LevelScene::onContactBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
	//scheduleOnce(CC_SCHEDULE_SELECTOR(LevelScene::updateStart), 0);



	this->scheduleUpdate();
	return true;
}

cocos2d::Scene * LevelScene::createScene()
{
	auto scene = Scene::createWithPhysics();

	// set gravity
	scene->getPhysicsWorld()->setGravity(Vec2(0, -1000));

	// optional: set debug draw
	//scene->getPhysicsWorld()->setDebugDrawMask(0xffff);
	scene->getPhysicsWorld()->step(1 / 60.0f);


	auto layer = LevelScene::create();
	scene->addChild(layer);

	return scene;
}
