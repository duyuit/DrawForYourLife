#include "MyUI.h"
#include "TestScene.h"
#include "TurtorialScene.h"
#include "LevelMap.h"
//Start
void MyUI::SetCurrentScene(Layer * scene)
{
	current_scene = scene;
	finish->current_scene = scene;
}
//End

void MyUI::DisableExcept(BUTTON_TAG tag)
{
	_touch_guide->setVisible(true);
	switch (tag)
	{
	case Define::BUTTON_LEFT:
		_button_right->setEnabled(false);
		_touch_guide->setPosition((_director->getWinSize().width / 3)/ 2, _director->getWinSize().height / 2);
		break;

	case Define::BUTTON_RIGHT:
		_button_left->setEnabled(false);
		_touch_guide->setPosition(_director->getWinSize().width - _director->getWinSize().width / 6, _director->getWinSize().height / 2);

		break;

	}
	_button_right->setOpacity(150);
	_button_left->setOpacity(150);
}

void MyUI::EnableAll()
{
	_button_right->setOpacity(0);
	_button_left->setOpacity(0);

	_button_left->setEnabled(true);
	_button_right->setEnabled(true);
	_touch_guide->setVisible(false);

}



MyUI::MyUI(Sonic * mSonic)
{
		mySonic = mSonic;

		_touch_guide = Sprite::create();
		auto animation = Animation::createWithSpriteFrames(Define::loadAnim("GameComponents/touch.xml", "1"), 0.03f);
		_touch_guide->runAction(RepeatForever::create(Animate::create(animation)));
		_touch_guide->setVisible(false);
		_touch_guide->setScale(0.6);
		_touch_guide->setAnchorPoint(Vec2(0.5, 0.5));
		this->addChild(_touch_guide);

		_button_left = Button::create(Define::button_left_grey_path);
		float delta_scale_x = (_director->getWinSize().width / 3)/_button_left->getContentSize().width;
		float delta_scale_y= _director->getWinSize().height / _button_left->getContentSize().height;
		_button_left->setScale(delta_scale_x, delta_scale_y);
		_button_left->setOpacity(0);
		_button_left->setPosition(Vec2(_button_left->getContentSize().width*delta_scale_x/2, 0));
		_button_left->setAnchorPoint(Vec2(0.5, 0));

		_button_left->addTouchEventListener([this](Ref* sender, Widget::TouchEventType type) {
			auto but = (Button*)sender;
			switch (type)
			{
			case ui::Widget::TouchEventType::BEGAN:
			//	but->setOpacity(255);
				break;
			case ui::Widget::TouchEventType::ENDED:
			//	but->setOpacity(200);
			
				mySonic->ActiveButton(BUTTON_TAG::BUTTON_LEFT);
				SimpleAudioEngine::getInstance()->playEffect(Define::_music_button_effect_path);
				break;
			default:
				break;
			}
		});
	
		this->addChild(_button_left, -1);



		_button_right = Button::create(Define::button_right_grey_path);
		_button_right->setScale(delta_scale_x, delta_scale_y);
		_button_right->setPosition(Vec2(_director->getWinSize().width - _button_left->getContentSize().width*delta_scale_x / 2, 0));
		_button_right->setAnchorPoint(Vec2(0.5, 0));
		_button_right->setOpacity(0);
		_button_right->addTouchEventListener([this](Ref* sender, Widget::TouchEventType type) {
			auto but = (Button*)sender;
			switch (type)
			{
			case ui::Widget::TouchEventType::BEGAN:
				//but->setOpacity(255);
				break;
			case ui::Widget::TouchEventType::ENDED:
					mySonic->ActiveButton(BUTTON_TAG::BUTTON_RIGHT);
					SimpleAudioEngine::getInstance()->playEffect(Define::_music_button_effect_path); 
					
				//but->setOpacity(200);
				break;
			default:
				break;
			}
		});
		this->addChild(_button_right, -1);

		//visibleSzie level map
		auto visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();
		float scaleX = visibleSize.width / 2;
		float scaleY = visibleSize.height / 2;

		//Board Star
		board = Sprite::create("Level_map/game_board.png");
		//board->setScale(origin.x /2, origin.y /2);
		board->setAnchorPoint(Vec2(0.5f, 0.5f));
		board->setOpacity(0);
		board->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
		board->setVisible(false);
		this->addChild(board, 5);

		layer = LayerColor::create();
		layer->setColor(Color3B::BLACK);
		layer->setOpacity(200);
		this->addChild(layer);
		layer->setVisible(false);

		//Define delta x size board
		float delta_x = board->getContentSize().width / 10;
		float delta_y = board->getContentSize().height * 2 / 5;
		//Define number scale button in Board Star
		float numScale = 0.9;

		//Label Board Star
		auto myLabel = Label::createWithTTF("Pausing", "fonts/hemi.ttf", 30);
		myLabel->setAnchorPoint(Vec2(0.5f, 0.5f));
		myLabel->setPosition(Vec2(delta_x * 6 - delta_x * 2 / 2, delta_y * 2.5 - delta_y / 2));
		board->addChild(myLabel, 2);

		//Button round in Board Star
		auto button_board_round = Button::create("Level_map/round.png");
		//button_board_round->setScale(numScale*scaleX, numScale*scaleY);
		button_board_round->setAnchorPoint(Vec2(0.5f, 0.5f));
		button_board_round->setPosition(Vec2(delta_x * 2 / 2, delta_y));
		board->addChild(button_board_round, 6);
		button_board_round->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
			switch (type)
			{
			case ui::Widget::TouchEventType::BEGAN:
				break;
			case ui::Widget::TouchEventType::ENDED:
			{
				_restart->setVisible(true);
				board->setVisible(false);
				if (current_scene != nullptr)
				{
					auto scene = (LevelScene*)current_scene;
					scene->ReloadScene();
				}
			}
				break;
			default:
				break;
			}
		});

		//Button play  in Board Star
		auto button_board_play = Button::create("Level_map/play.png");
		//button_board_play->setScale(numScale*scaleX, numScale*scaleY);
		button_board_play->setAnchorPoint(Vec2(0.5f, 0.5f));
		button_board_play->setPosition(Vec2(delta_x * 10 / 2, delta_y));
		board->addChild(button_board_play, 6);
		button_board_play->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
			switch (type)
			{
			case ui::Widget::TouchEventType::BEGAN:
				break;
			case ui::Widget::TouchEventType::ENDED:
			{
				_restart->setVisible(true);
				board->setVisible(false);
				layer->setVisible(false);
				if (current_scene != nullptr)
				{
					auto scene = (LevelScene*)current_scene;
					scene->MyResume();
				}
			}
				break;
			default:
				break;
			}
		});

		//Button cancel in Board Star
		auto button_board_cancel = Button::create("Level_map/out.png");
		//button_board_cancel->setScale(numScale*scaleX, numScale*scaleY);
		button_board_cancel->setAnchorPoint(Vec2(0.5f, 0.5f));
		button_board_cancel->setPosition(Vec2(delta_x * 19 / 2, delta_y));
		board->addChild(button_board_cancel, 6);

		button_board_cancel->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
			switch (type)
			{
			case ui::Widget::TouchEventType::BEGAN:
				break;
			case ui::Widget::TouchEventType::ENDED:
			{
				//setEnabledAll(true);
				_restart->setVisible(true);
				board->setVisible(false);
				layer->setVisible(false);

				auto gameScene = LevelMap::createScene();
				Director::getInstance()->replaceScene(TransitionFade::create(1, gameScene));
			}
				break;
			default:
				break;
			}
		});

		_restart = Button::create("Level_map/pause.png");
		_restart->setPosition(_director->getWinSize() - _restart->getContentSize());
		_restart->setScale(0.8);
		_restart->setAnchorPoint(Vec2(0.5, 0.5));
		_restart->addTouchEventListener([this](Ref* sender, Widget::TouchEventType type) {
			auto but = (Button*)sender;
			switch (type)
			{
			case ui::Widget::TouchEventType::BEGAN:
				break;
			case ui::Widget::TouchEventType::ENDED: {
				_restart->setVisible(false);
				board->setVisible(true);
				layer->setVisible(true);
				if (current_scene != nullptr)
				{
					auto scene = (LevelScene*)current_scene;
					scene->MyPause();
				}
			}
				break;
			default:
				break;
			}
		});
		this->addChild(_restart, -1);

		//Add label Ring-Combo-Score
		_combo = new RingComboScore(mSonic);
		this->addChild(_combo, 1);
		
		touch_ani = new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(Define::loadAnim("GameComponents/ripple.xml","1"), 0.008f)));
		auto listener1 = EventListenerTouchOneByOne::create();

		listener1->onTouchBegan = [this](Touch* touch, Event* event) {
			//start_touch_position = touch->getLocation();
			return true;
		};

		// trigger when you let up
		listener1->onTouchEnded = [this](Touch* touch, Event* event) {
			auto sprite = Sprite::create();
			sprite->setScale(0.7);
			sprite->setOpacity(200);
			sprite->setPosition(touch->getLocation());
			this->getParent()->addChild(sprite);
			sprite->runAction(Sequence::create(touch_ani->get()->clone(), RemoveSelf::create(), nullptr));
				_istouch = true;
			
		};

		auto eventListener = EventListenerKeyboard::create();
		eventListener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event) {
	


		};
		eventListener->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event* event) {

			if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW)
			{
				/*auto scene =(LevelScene*) current_scene;
				scene->NextScene();*/


				mySonic->ActiveButton(BUTTON_TAG::BUTTON_LEFT);
			}
			else if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
			{
			//	mySonic->mJustTap = BUTTON_TAG::BUTTON_RIGHT;
				mySonic->ActiveButton(BUTTON_TAG::BUTTON_RIGHT);
			}

		};
		_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener, this);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, this);
	//	this->autorelease();
		this->scheduleUpdate();
};

void MyUI::update(float dt)
{
	count_to_reset_touch++;
	if (count_to_reset_touch ==5)
	{
		count_to_reset_touch = 0;
		_istouch = false;
	}

	//Start
	if (mySonic->isFinish)
	{
		count_to_finish++;
		if (count_to_finish >= 150)
		{
			finish = new FinishLayer(mySonic, current_scene);
			this->addChild(finish, 100);
			_restart->setVisible(false);
			layer = LayerColor::create();
			layer->setColor(Color3B::BLACK);
			layer->setOpacity(200);
			this->addChild(layer);
			layer->setVisible(true);
			mySonic->isFinish = false;
		}
	}
	//End
}