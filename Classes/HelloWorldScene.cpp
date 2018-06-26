/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
	auto scene = Scene::createWithPhysics();

	// set gravity
	scene->getPhysicsWorld()->setGravity(Vec2(0, -980));

	// optional: set debug draw
	scene->getPhysicsWorld()->setDebugDrawMask(0xffff);
	scene->getPhysicsWorld()->step(1 / 60.0f);

	

	auto layer = HelloWorld::create();
	scene->addChild(layer);

	return scene;
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Layer::init())
    {
        return false;
    }
	
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
	Size winSize = Director::getInstance()->getWinSize();

	


	_tileMap = new TMXTiledMap();
	_tileMap->initWithTMXFile("snow_map.tmx");
	this->addChild(_tileMap);
	LoadMap(_tileMap);

	

	mSonic = new Sonic();
	this->addChild(mSonic);
	//mSonic->AddLightning();
	
	
	
	LandMonster *abc = new LandMonster();
	abc->setPosition(100, 300);
	this->addChild(abc);
	
	auto listener1 = EventListenerTouchOneByOne::create();

	listener1->onTouchBegan = [this](Touch* touch, Event* event) {
		start_touch_position = touch->getLocation();
		return true;
	};
	
	
	//Parallax Scrolling
	_backgroundNode = InfiniteParallaxNode::create();
	auto _galaxy = Sprite::create("stone_bg1.png"); _galaxy->setAnchorPoint(Point(0, 0.5));
	_backgroundNode->addChild(_galaxy, -1, Point(5, 0), Point(0, winSize.height * 0.7));
	this->addChild(_backgroundNode, -1);


	TapButton *daidi = new TapButton(1, Vec2(1500, 200),mSonic,this);


	// trigger when you let up
	listener1->onTouchEnded = [this](Touch* touch, Event* event) {
		end_touch_position = touch->getLocation();
		mSonic->handle_swipe(start_touch_position, end_touch_position);
	};

    
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, this);


	

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(HelloWorld::onContactBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
	scheduleOnce(CC_SCHEDULE_SELECTOR(HelloWorld::updateStart),0);
	


	this->scheduleUpdate();

    return true;
}

void HelloWorld::update(float dt)
{    
	for (int i = 0; i < 3; ++i)
	{
		this->getScene()->getPhysicsWorld()->step(1 / 60.0f);
	}
	//_backgroundNode->setPosition(_backgroundNode->getPosition() - Vec2(2, 0));
	//_backgroundNode->updatePosition();
	mSonic->update();

	if (mSonic->getPosition().x < 0) mSonic->setPosition(0, mSonic->getPosition().y);
	setViewPointCenter(mSonic->getPosition());

	
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);

}

void HelloWorld::updateStart(float dt)
{
	//this->getScene()->getPhysicsWorld()->setFixedUpdateRate(60);
	auto x_button = Button::create("Button/button_x.png");
	x_button->setScale(0.5);
	x_button->setOpacity(200);
	x_button->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
		auto but = (Button*)sender;
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
				but->setOpacity(255);
				break;
		case ui::Widget::TouchEventType::ENDED:
				but->setOpacity(200);
				break;
		default:
			break;
		}
	});
	x_button->setPosition(Vec2(100,50));
	this->getScene()->addChild(x_button, 1);

	auto button_rect = Button::create("Button/button_rect.png");
	button_rect->setScale(0.5);
	button_rect->setOpacity(200);
	button_rect->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
		auto but = (Button*)sender;
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			but->setOpacity(255);
			break;
		case ui::Widget::TouchEventType::ENDED:
			but->setOpacity(200);
			break;
		default:
			break;
		}
	});
	button_rect->setPosition(Vec2(50, 100));
	this->getScene()->addChild(button_rect, 1);


	auto button_trian = Button::create("Button/button_trian.png");
	button_trian->setScale(0.5);
	button_trian->setOpacity(200);
	button_trian->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
		auto but = (Button*)sender;
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			but->setOpacity(255);
			break;
		case ui::Widget::TouchEventType::ENDED:
			but->setOpacity(200);
			break;
		default:
			break;
		}
	});
	button_trian->setPosition(Vec2(100, 150));
	this->getScene()->addChild(button_trian, 1);


	auto button_cir = Button::create("Button/button_cir.png");
	button_cir->setScale(0.5);
	button_cir->setOpacity(200);
	button_cir->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
		auto but = (Button*)sender;
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			but->setOpacity(255);
			break;
		case ui::Widget::TouchEventType::ENDED:
			but->setOpacity(200);
			break;
		default:
			break;
		}
	});
	button_cir->setPosition(Vec2(150, 100));
	this->getScene()->addChild(button_cir, 1);
}



void HelloWorld::LoadMap(CCTMXTiledMap * map)
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

			this->addChild(edgeSp); // Add vào Layer
		}



		//TMXObjectGroup *objectGroup_hold_land = _tileMap->getObjectGroup("HoldLand");


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

		//	this->addChild(edgeSp); // Add vào Layer
		//}


		//TMXObjectGroup *objectGroup_ring = _tileMap->getObjectGroup("Ring");


		//for (int i = 0; i < objectGroup_ring->getObjects().size(); i++)
		//{

		//	Value objectemp = objectGroup_ring->getObjects().at(i);

		//	float wi_box = objectemp.asValueMap().at("width").asFloat();
		//	float he_box = objectemp.asValueMap().at("height").asFloat();
		//	float x_box = objectemp.asValueMap().at("x").asFloat() + wi_box / 2;
		//	float y_box = objectemp.asValueMap().at("y").asFloat() + he_box / 2;

		//	auto ring = new small_Ring();
		//	ring->setPosition(x_box, y_box);
		//	this->addChild(ring);
		//}



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

void HelloWorld::setViewPointCenter(Point position)
{

	Size winSize = _director->getWinSize();

	int x = MAX(position.x, winSize.width / 2);
	int y = MAX(position.y, winSize.height / 2);
	x = MIN(x, (_tileMap->getMapSize().width * this->_tileMap->getTileSize().width) - winSize.width / 2);
	y = MIN(y, (_tileMap->getMapSize().height * _tileMap->getTileSize().height) - winSize.height / 2);
	Vec2 actualPosition = Vec2(x, y);

	Vec2 centerOfView = Vec2(winSize.width / 2, winSize.height / 2);
	Vec2 viewPoint = centerOfView - actualPosition;
//	this->setPosition3D(Vec3(viewPoint.x,viewPoint.y,50));
	this->setPosition(viewPoint);
	//this->getScene()->getDefaultCamera()->setPosition(-viewPoint);
}

bool HelloWorld::onContactBegin(cocos2d::PhysicsContact& contact) 
{
	auto spriteA = (Sprite*)contact.getShapeA()->getBody()->getNode(); // 1
	auto spriteB = (Sprite*)contact.getShapeB()->getBody()->getNode(); // 2

	int tagA = spriteA->getTag();                                      // 3
	int tagB = spriteB->getTag();        

	if (tagA == Define::Player || tagB == Define::Player )
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