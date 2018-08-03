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

#include "MenuScene.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;
USING_NS_CC;
using namespace std;
using namespace ui;
Scene* MenuScene::createScene()
{
    return MenuScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool MenuScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto audio = SimpleAudioEngine::getInstance();
	//audio->preloadBackgroundMusic("music.mp3");
	//audio->playBackgroundMusic("music.mp3");
	/*
	// Menu Item sử dụng văn bản.
	// Khởi tạo một Label có tên là myLabel.
	//auto myLabel = Label::create("Play", "fonts/Marker Felt.ttf", 24);
	//auto myLabel2 = Label::create("Exit", "fonts/Marker Felt.ttf", 24);
	auto playImage1 = Sprite::create("playbutton1.png");
	auto playImage = Sprite::create("playbutton.png");
	playImage1->setScale(1.5,1.5);
	playImage->setScale(1.5, 1.5);
	auto playButton = MenuItemImage::create(
		playImage1,
		playImage,
		CC_CALLBACK_1(HelloWorld::menuPlay, this));
	// Thiết lập vị trí của closeItem tại vị trí (100, 150).
	playButton->setPosition(Vec2(0, 0));
	// Khởi tạo một mảng Vector kiểu MenuItemLabel.
	Vector<MenuItem*> menuItems;

	// Thêm Menu Item closeItem vào menuItems.
	//menuItems.pushBack(labelPlay);
	menuItems.pushBack(playButton);
	// Tạo một Menu có tên là menu với mảng Vector menuItems.
	auto menu = Menu::createWithArray(menuItems);
	// Thêm vào Scence hiện tại của bạn.
	this->addChild(menu, 1);
	*/
	

	
	auto background = Sprite::create("Menu/game_background.png");
	background->setScale(visibleSize.width / background->getContentSize().width, visibleSize.height / background->getContentSize().height);
	background->setAnchorPoint(Vec2(0.0f, 0.0f));
	background->setPosition(Vec2(0, 0));
	this->addChild(background, 0);

	float scaleX = visibleSize.width / background->getContentSize().width;
	float scaleY = visibleSize.height / background->getContentSize().height;
	//auto label = Label::createWithTTF(std::to_string(scaleX) + " " + std::to_string(scaleY), "fonts/arial.ttf", 24);
	//label->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	//this->addChild(label, 100);

	auto tittle = Sprite::create("Menu/tittle_game_2.png");
	tittle->setAnchorPoint(Vec2(0.5f, 0.5f));
	tittle->setScale(0.5*scaleX,0.5*scaleY);
	tittle->runAction(RepeatForever::create(Sequence::create(MoveBy::create(1, Vec2(0, 10)), MoveBy::create(1, Vec2(0, -10)), nullptr)));
	tittle->setPosition(Vec2(visibleSize.width / 3, 0.8 * visibleSize.height));
	this->addChild(tittle, 2);

	auto button_play = Button::create("Menu/btn_play.png");
	button_play->setScale(0.3 * scaleX, 0.3 * scaleY);
	button_play->setAnchorPoint(Vec2(0.5f, 0.5f));
	button_play->setPosition(Vec2(visibleSize.width / 3, 0.5 * visibleSize.height));
	button_play->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
		{	
			SimpleAudioEngine::getInstance()->playEffect(Define::_music_btn_effect_1_path);
			SimpleAudioEngine::getInstance()->stopBackgroundMusic();
			SimpleAudioEngine::getInstance()->playBackgroundMusic(Define::_music_menu_scene_background_2_path);
			auto myScene = SelectMap::createScene();
			Director::getInstance()->replaceScene(TransitionFade::create(1, myScene));		
		}
			break;
		default:
			break;
		}
	});
	this->addChild(button_play,1);

	auto button_option = Button::create("Menu/btn_option.png");
	button_option->setScale(0.3 * scaleX, 0.3 * scaleY);
	button_option->setAnchorPoint(Vec2(0.5, 0.5));
	button_option->setPosition(Vec2(visibleSize.width / 3, (0.5 * visibleSize.height) - (visibleSize.height / 6 )));
	button_option->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
		{
			SimpleAudioEngine::getInstance()->playEffect(Define::_music_btn_effect_1_path);
		}
		break;
		default:
			break;
		}
	});
	this->addChild(button_option, 1);

	auto button_quit = Button::create("Menu/btn_quit.png");
	button_quit->setScale(0.3 * scaleX, 0.3 * scaleY);
	button_quit->setAnchorPoint(Vec2(0.5, 0.5));
	button_quit->setPosition(Vec2(visibleSize.width / 3, (0.5 * visibleSize.height) - (visibleSize.height / 3 )));
	button_quit->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
		{
			Director::getInstance()->end();
			#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
						exit(0);
			#endif
		}
		break;
		default:
			break;
		}
	});
	this->addChild(button_quit, 1);

	return true;
}


void MenuScene::menuCloseCallback(Ref* pSender)
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



