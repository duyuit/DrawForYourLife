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
	scene->getPhysicsWorld()->setGravity(Vec2(0, -900));

	// optional: set debug draw
	// scene->getPhysicsWorld()->setDebugDrawMask(0xffff);

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


	//test


	_tileMap = new TMXTiledMap();
	_tileMap->initWithTMXFile("untitled.tmx");
	//_tileMap->setScale(0.3f);
	this->addChild(_tileMap);


	TMXObjectGroup *objectGroup = _tileMap->getObjectGroup("Land");


	for (int i = 0; i<objectGroup->getObjects().size(); i++)
	{

		Value objectemp = objectGroup->getObjects().at(i);

		float wi_box = objectemp.asValueMap().at("width").asFloat();
		float he_box = objectemp.asValueMap().at("height").asFloat();
		float x_box = objectemp.asValueMap().at("x").asFloat() + wi_box / 2;
		float y_box = objectemp.asValueMap().at("y").asFloat() + he_box / 2;

		auto edgeSp = Sprite::create();
		auto boundBody = PhysicsBody::createBox(Size(wi_box, he_box));
		boundBody->getShape(0)->setFriction(10.0f);
		boundBody->setDynamic(false);
		boundBody->getShape(0)->setRestitution(100.0f);
		boundBody->setContactTestBitmask(0x1);
		edgeSp->setPhysicsBody(boundBody);
		edgeSp->setPosition(Vec2(x_box, y_box));

		this->addChild(edgeSp); // Add vào Layer
	}



	mSonic = new Sonic();
	this->addChild(mSonic);
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


	
	Sprite* border = Sprite::create("loadingbar.png");
	border->setAnchorPoint(Vec2(0.5, 0.5));
	border->setPosition(Vec2(543, 384));
	this->addChild(border, 5);

	Sprite* background = Sprite::create("loadingbar_state.png");
	background->setAnchorPoint(Vec2(0.0, 0.0));
	background->setPosition(Vec2(0.0, 0.0));
	//barBody->addChild(background, 0, kBar);

	ProgressTimer* mouseBar = ProgressTimer::create(background);
	mouseBar->setType(ProgressTimerType::BAR);
	mouseBar->setAnchorPoint(Vec2(0.0, 0.0));
	mouseBar->setPosition(Vec2(0.0, 0.0));
	mouseBar->setBarChangeRate(Vec2(1, 0));
	mouseBar->setMidpoint(Vec2(0.0, 0.0));
	mouseBar->setPercentage(34);
	border->addChild(mouseBar, 10);

	mouseBar->runAction(ProgressFromTo::create(2.0f, 30.0f, 100)); // filling from 30% to 75% in 2 seconds
	this->scheduleUpdate();

    return true;
}

void HelloWorld::update(float dt)
{
	mSonic->update();
	if (mSonic->getPosition().x < 0) mSonic->setPosition(0, mSonic->getPosition().y);
//	if (mSonic->getPosition().x > Director::getInstance()->getVisibleSize().width) mSonic->setPosition(Director::getInstance()->getVisibleSize().width, mSonic->getPosition().y);
	//auto camera = this->getScene()->getDefaultCamera();
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
	this->setPosition(viewPoint);
}
