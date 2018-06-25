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
	scene->getPhysicsWorld()->setGravity(Vec2(0, -1200));

	// optional: set debug draw
	 scene->getPhysicsWorld()->setDebugDrawMask(0xffff);

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


	


	_tileMap = new TMXTiledMap();
	_tileMap->initWithTMXFile("untitled.tmx");
	//_tileMap->setScale(0.3f);
	this->addChild(_tileMap);
	LoadMap(_tileMap);

	

	mSonic = new Sonic();
	this->addChild(mSonic);
	mSonic->AddLightning();
	
	
	
	LandMonster *abc = new LandMonster();
	abc->setPosition(100, 300);
	this->addChild(abc);
	
	auto listener1 = EventListenerTouchOneByOne::create();

	listener1->onTouchBegan = [this](Touch* touch, Event* event) {
		start_touch_position = touch->getLocation();
		return true;
	};
	
	

	// trigger when you let up
	listener1->onTouchEnded = [this](Touch* touch, Event* event) {
		end_touch_position = touch->getLocation();
		mSonic->handle_swipe(start_touch_position, end_touch_position);
	};

    
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, this);


	


	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(HelloWorld::onContactBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

	this->scheduleUpdate();


    return true;
}

void HelloWorld::update(float dt)
{
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



void HelloWorld::LoadMap(CCTMXTiledMap * map)
{
	TMXObjectGroup *objectGroup_land = _tileMap->getObjectGroup("Land");


	for (int i = 0; i<objectGroup_land->getObjects().size(); i++)
	{

		Value objectemp = objectGroup_land->getObjects().at(i);

		float wi_box = objectemp.asValueMap().at("width").asFloat();
		float he_box = objectemp.asValueMap().at("height").asFloat();
		float x_box = objectemp.asValueMap().at("x").asFloat() + wi_box / 2;
		float y_box = objectemp.asValueMap().at("y").asFloat() + he_box / 2;

		auto edgeSp = Sprite::create();
		auto boundBody = PhysicsBody::createBox(Size(wi_box, he_box));
		boundBody->getShape(0)->setFriction(10.0f);
		boundBody->setDynamic(false);
		boundBody->getShape(0)->setRestitution(100.0f);

		boundBody->setCategoryBitmask(2);
		boundBody->setCollisionBitmask(1);
		boundBody->setContactTestBitmask(1);

		edgeSp->setPhysicsBody(boundBody);
		edgeSp->setPosition(Vec2(x_box, y_box));

		this->addChild(edgeSp); // Add vào Layer
	}



	TMXObjectGroup *objectGroup_hold_land = _tileMap->getObjectGroup("HoldLand");


	for (int i = 0; i<objectGroup_hold_land->getObjects().size(); i++)
	{

		Value objectemp = objectGroup_hold_land->getObjects().at(i);

		float wi_box = objectemp.asValueMap().at("width").asFloat();
		float he_box = objectemp.asValueMap().at("height").asFloat();
		float x_box = objectemp.asValueMap().at("x").asFloat() + wi_box / 2;
		float y_box = objectemp.asValueMap().at("y").asFloat() + he_box / 2;

		auto edgeSp = Sprite::create();
		edgeSp->setTag(Define::HoldPlace);
		auto boundBody = PhysicsBody::createBox(Size(wi_box, he_box));
		boundBody->getShape(0)->setFriction(10.0f);
		boundBody->setDynamic(false);
		boundBody->getShape(0)->setRestitution(100.0f);

		
		boundBody->setCategoryBitmask(4);
		boundBody->setCollisionBitmask(1);
		boundBody->setContactTestBitmask(1);



		edgeSp->setPhysicsBody(boundBody);
		edgeSp->setPosition(Vec2(x_box, y_box));

		this->addChild(edgeSp); // Add vào Layer
	}


	TMXObjectGroup *objectGroup_ring = _tileMap->getObjectGroup("Ring");


	for (int i = 0; i<objectGroup_ring->getObjects().size(); i++)
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
}

bool HelloWorld::onContactBegin(cocos2d::PhysicsContact& contact) 
{
	auto spriteA = (Sprite*)contact.getShapeA()->getBody()->getNode(); // 1
	auto spriteB = (Sprite*)contact.getShapeB()->getBody()->getNode(); // 2

	int tagA = spriteA->getTag();                                      // 3
	int tagB = spriteB->getTag();                                      // 4
	if ((tagA == Define::Player && tagB == Define::HoldPlace) || (tagA == Define::HoldPlace && tagB ==Define::Player))
	{
		if (tagA == Define::Player)
		{
			Sonic *sonic = (Sonic*)spriteA;
			sonic->SetStateByTag(SonicState::StateAction::HOLD);
			sonic->setPosition(spriteB->getPosition());
		}
		else
		{
			Sonic *sonic = (Sonic*)spriteB;
			sonic->SetStateByTag(SonicState::StateAction::HOLD);
			sonic->setPosition(spriteB->getPosition());
		}
	}
	if (tagA == Define::Player && tagB == Define::Ring || tagA == Define::Ring && tagB == Define::Player)
	{
	
		if (tagA == Define::Player)
		{
			spriteB->runAction(RemoveSelf::create());
			MyParticle::CreateEatItem(spriteB->getPosition(), this);
		}
		else
		{
			spriteA->runAction(RemoveSelf::create());
			MyParticle::CreateEatItem(spriteA->getPosition(), this);
		}
	}
	return true;
}