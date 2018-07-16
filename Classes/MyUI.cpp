#include "MyUI.h"
#include "TestScene.h"
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
		_touch_guide->setPosition((_director->getWinSize().width / 3)*(5 / 2), _director->getWinSize().height / 2);

		break;

	}

}

void MyUI::EnableAll()
{
	
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

		_button_left = Button::create("GameComponents/black_button.png");
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
		
				mySonic->mJustTap = BUTTON_TAG::BUTTON_LEFT;
				mySonic->_list_just_tap.push_back(BUTTON_TAG::BUTTON_LEFT);
				SimpleAudioEngine::getInstance()->playEffect(Define::_music_button_effect_path);
				break;
			default:
				break;
			}
		});
	
		this->addChild(_button_left, -1);



		_button_right = Button::create("GameComponents/black_button.png");
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
				mySonic->mJustTap = BUTTON_TAG::BUTTON_RIGHT;
				mySonic->_list_just_tap.push_back(BUTTON_TAG::BUTTON_RIGHT);
				SimpleAudioEngine::getInstance()->playEffect(Define::_music_button_effect_path);
				//but->setOpacity(200);
				break;
			default:
				break;
			}
		});
		this->addChild(_button_right, -1);

		_restart = Button::create("Level_map/round.png");
		_restart->setPosition(_director->getWinSize() - _restart->getContentSize());
		_restart->setAnchorPoint(Vec2(0.5, 0.5));
		_restart->addTouchEventListener([this](Ref* sender, Widget::TouchEventType type) {
			auto but = (Button*)sender;
			switch (type)
			{
			case ui::Widget::TouchEventType::BEGAN:
				//but->setOpacity(255);
				break;
			case ui::Widget::TouchEventType::ENDED:
				Director::getInstance()->replaceScene(TestScene::createScene());
				//but->setOpacity(200);
				break;
			default:
				break;
			}
		});
		this->addChild(_restart, -1);


		//Add Sprite ring
		ringIcon = Sprite::create("Item/ring.png", Rect(200, 48, 64, 50));
		ringIcon->setPosition(Vec2(50, _director->getWinSize().height - ringIcon->getContentSize().height));
		this->addChild(ringIcon, 1);

		//Add label count rings
		countRing = Label::createWithTTF("X  " + std::to_string(mSonic->ringCollected), "fonts/Marker Felt.ttf", 36);
		countRing->setPosition(Vec2(125, _director->getWinSize().height - ringIcon->getContentSize().height));
		this->addChild(countRing, 1);
		this->scheduleUpdate();

		//Add label combo score
		_combo = new ComboScore(mSonic);
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
				//mySonic->countCombo = 10;
				mySonic->mJustTap = BUTTON_TAG::BUTTON_LEFT;
				mySonic->_list_just_tap.push_back(BUTTON_TAG::BUTTON_LEFT);
			}
			else if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
			{
				mySonic->mJustTap = BUTTON_TAG::BUTTON_RIGHT;
				mySonic->_list_just_tap.push_back(BUTTON_TAG::BUTTON_RIGHT);
			}

		};
		_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener, this);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, this);
};