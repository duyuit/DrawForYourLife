#include "TurtorialScene.h"

cocos2d::Scene * TurtorialScene::createScene()
{
	auto scene = Scene::createWithPhysics();

	// set gravity
	scene->getPhysicsWorld()->setGravity(Vec2(0, -1000));

	// optional: set debug draw
	//scene->getPhysicsWorld()->setDebugDrawMask(0xffff);
	//scene->getPhysicsWorld()->step(1 / 60.0f);



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

void TurtorialScene::Pause()
{
	isPause = true;
	for (auto label : listLabel)
	{
		label->setVisible(true);
	}
	blackImage->setVisible(true);
}

void TurtorialScene::Continue()
{
	isPause = false;
	mSonic->SetVelocityX(340);
	for (auto label : listLabel)
	{
		label->setVisible(false);
	}
	blackImage->setVisible(false);
}

void TurtorialScene::LoadMap(CCTMXTiledMap * map)
{
	try
	{
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
			boundBody->setCollisionBitmask(1);
			boundBody->setContactTestBitmask(1);

			edgeSp->setPhysicsBody(boundBody);
			edgeSp->setPosition(Vec2(x_box, y_box));

			this->addChild(edgeSp); // Add v�o Layer
		}



		{//TMXObjectGroup *objectGroup_hold_land = _tileMap->getObjectGroup("HoldLand");


		 //for (int i = 0; i < objectGroup_hold_land->getObjects().size(); i++)
		 //{

		 //	Value objectemp = objectGroup_hold_land->getObjects().at(i);

		 //	float wi_box = objectemp.asValueMap().at("width").asFloat();
		 //	float he_box = objectemp.asValueMap().at("height").asFloat();
		 //	float x_box = objectemp.asValueMap().at("x").asFloat() + wi_box / 2;
		 //	float y_box = objectemp.asValueMap().at("y").asFloat() + he_box / 2;

		 //	auto edgeSp = Sprite::create();
		 //	edgeSp->setTag(Define::HoldPlace);
		 //	auto boundBody = PhysicsBody::createBox(Size(wi_box, he_box));
		 //	boundBody->getShape(0)->setFriction(10.0f);
		 //	boundBody->setDynamic(false);
		 //	boundBody->getShape(0)->setRestitution(100.0f);


		 //	boundBody->setCategoryBitmask(4);
		 //	boundBody->setCollisionBitmask(1);
		 //	boundBody->setContactTestBitmask(1);



		 //	edgeSp->setPhysicsBody(boundBody);
		 //	edgeSp->setPosition(Vec2(x_box, y_box));

		 //	this->addChild(edgeSp); // Add v�o Layer
		 //}


			/*TMXObjectGroup *objectGroup_ring = _tileMap->getObjectGroup("Ring");


			for (int i = 0; i < objectGroup_ring->getObjects().size(); i++)
			{

				Value objectemp = objectGroup_ring->getObjects().at(i);

				float wi_box = objectemp.asValueMap().at("width").asFloat();
				float he_box = objectemp.asValueMap().at("height").asFloat();
				float x_box = objectemp.asValueMap().at("x").asFloat() + wi_box / 2;
				float y_box = objectemp.asValueMap().at("y").asFloat() + he_box / 2;

				auto ring = new small_Ring();
				ring->setPosition(x_box, y_box);
				this->addChild(ring);
			}
*/


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
		TMXObjectGroup *objectGroup_button = _tileMap->getObjectGroup("Button");


		for (int i = 0; i < objectGroup_button->getObjects().size(); i++)
		{

			Value objectemp = objectGroup_button->getObjects().at(i);

			float wi_box = objectemp.asValueMap().at("width").asFloat();
			float he_box = objectemp.asValueMap().at("height").asFloat();
			float x_box = objectemp.asValueMap().at("x").asFloat() + wi_box / 2;
			float y_box = objectemp.asValueMap().at("y").asFloat() + he_box / 2;

			int a = RandomHelper::random_int(1, 4);
			auto button = new TapButton(a, Vec2(x_box, y_box), mSonic, this);
			listButton.pushBack(button);
		}

		TMXObjectGroup *objectGroup_text = _tileMap->getObjectGroup("Text");


		for (int i = 0; i < objectGroup_text->getObjects().size(); i++)
		{

			Value objectemp = objectGroup_text->getObjects().at(i);

			float wi_box = objectemp.asValueMap().at("width").asFloat();
			float he_box = objectemp.asValueMap().at("height").asFloat();
			float x_box = objectemp.asValueMap().at("x").asFloat() + wi_box / 2;
			float y_box = objectemp.asValueMap().at("y").asFloat() + he_box / 2;

			auto myLabel = Label::createWithTTF("Welcome to Sonic world, I am your Guider\n(Tap to continue)", "fonts/times.ttf", 24);
			myLabel->setPosition(x_box, y_box);
			this->addChild(myLabel,7);
			listLabel.pushBack(myLabel);
		}




	}
	catch (...) {};


}

void TurtorialScene::setViewPointCenter(Point position)
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
			Sonic *sonic = (Sonic*)spriteA;
			sonic->handle_collision(spriteB);
		}
		else
		{
			Sonic *sonic = (Sonic*)spriteB;
			sonic->handle_collision(spriteA);
		}
	}

	return true;
}
int count_to_move_scene = 0;
int delta_x = -30;
void TurtorialScene::update(float dt)
{
	
	_backgroundNode->setPosition(_backgroundNode->getPosition() - Vec2(5, 0));
	_backgroundNode->updatePosition();
	_backgroundNode2->setPosition(_backgroundNode2->getPosition() - Vec2(5, 0));
	_backgroundNode2->updatePosition();


	//mSonic->update(dt);
	if (isPause)
	{
		count_to_move_scene++;
		mSonic->SetVelocityX(0);
		auto pos_scene = this->getPosition();
		auto sonic_pos = mSonic->getPosition();
		this->setPosition((Vec2(delta_x,0)*_director->getDeltaTime() + pos_scene));
		//this->mSonic->setPosition(sonic_pos + Vec2(delta_x/2, 0));


		if (count_to_move_scene == 120)
		{
			count_to_move_scene = 0;
			delta_x *= -1;
		}
	}
	else
	{
		if (mSonic->getPosition().x < 0) mSonic->setPosition(0, mSonic->getPosition().y);
		setViewPointCenter(mSonic->getPosition());

	}

}

void TurtorialScene::updateStart(float dt)
{
	this->getScene()->addChild(new MyUI(mSonic), 5);

	
}

bool TurtorialScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	srand(time(NULL));
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	Size winSize = Director::getInstance()->getWinSize();




	_tileMap = new TMXTiledMap();
	_tileMap->initWithTMXFile("TurtorialScene/untitled.tmx");
	this->addChild(_tileMap);



	mSonic = new Sonic();
	mSonic->setPosition(200, 200);
	this->addChild(mSonic);


	LoadMap(_tileMap);



	//2 Parallax Scrolling
	_backgroundNode = InfiniteParallaxNode::create();

	auto _galaxy = Sprite::create("Map_stone/stone_bg3.png");
	_galaxy->setAnchorPoint(Point(0, 0));
	_galaxy->setScale(visibleSize.width / _galaxy->getContentSize().width); //auto scale background fitting screen
	_backgroundNode->addChild(_galaxy, -1, Point(0.9, 1), Point(0, 0));
	this->addChild(_backgroundNode, -1);

	_backgroundNode2 = InfiniteParallaxNode::create();

	auto _galaxy2 = Sprite::create("Map_stone/stone_bg3.png");
	_galaxy2->setAnchorPoint(Point(0, 0));
	_galaxy2->setScale(visibleSize.width / _galaxy->getContentSize().width); //auto scale background fitting screen
	_backgroundNode2->addChild(_galaxy2, -1, Point(0.9, 1), Point(_galaxy2->getContentSize().width * _galaxy->getScale(), 0));
	this->addChild(_backgroundNode2, -1);


	blackImage = Sprite::create("TurtorialScene/black.png");
	blackImage->setColor(Color3B(0, 0, 0));
	blackImage->setScale(20);
	blackImage->setOpacity(100);
	this->addChild(blackImage, 6);

	mSonic->setZOrder(7);


	

	auto listener1 = EventListenerTouchOneByOne::create();

	listener1->onTouchBegan = [this](Touch* touch, Event* event) {
		start_touch_position = touch->getLocation();
		return true;
	};

	// trigger when you let up
	listener1->onTouchEnded = [this](Touch* touch, Event* event) {
		end_touch_position = touch->getLocation();
		mSonic->handle_swipe(start_touch_position, end_touch_position);
		if (isPause) Continue();
	};


	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, this);




	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(TurtorialScene::onContactBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
	scheduleOnce(CC_SCHEDULE_SELECTOR(TurtorialScene::updateStart), 0);



	this->scheduleUpdate();
	Pause();
	return true;
}

