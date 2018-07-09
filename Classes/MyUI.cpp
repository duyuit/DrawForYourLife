#include "MyUI.h"

void MyUI::DisableExcept(BUTTON_TAG tag)
{
	switch (tag)
	{
	case Define::BUTTON_LEFT:
		_button_right->setEnabled(false);
		break;

	case Define::BUTTON_RIGHT:
		_button_left->setEnabled(false);
		break;

	}

}

void MyUI::EnableAll()
{
	
	_button_left->setEnabled(true);
	_button_right->setEnabled(true);

}

MyUI::MyUI(Sonic * mSonic)
{
		mySonic = mSonic;
	

		_button_left = Button::create(Define::button_left_green_path);
		_button_left->setScale(0.8);
		_button_left->setOpacity(200);
		_button_left->addTouchEventListener([this](Ref* sender, Widget::TouchEventType type) {
			auto but = (Button*)sender;
			switch (type)
			{
			case ui::Widget::TouchEventType::BEGAN:
				but->setOpacity(255);
				break;
			case ui::Widget::TouchEventType::ENDED:
				but->setOpacity(200);
				mySonic->mJustTap = BUTTON_TAG::BUTTON_LEFT;
				mySonic->_list_just_tap.push_back(BUTTON_TAG::BUTTON_LEFT);
				break;
			default:
				break;
			}
		});
		_button_left->setPosition(Vec2(50, 130));
		this->addChild(_button_left, 1);



		_button_right = Button::create(Define::button_right_green_path);
		_button_right->setScale(0.8);
		_button_right->setOpacity(200);
		_button_right->addTouchEventListener([this](Ref* sender, Widget::TouchEventType type) {
			auto but = (Button*)sender;
			switch (type)
			{
			case ui::Widget::TouchEventType::BEGAN:
				but->setOpacity(255);
				break;
			case ui::Widget::TouchEventType::ENDED:
				mySonic->mJustTap = BUTTON_TAG::BUTTON_RIGHT;
				mySonic->_list_just_tap.push_back(BUTTON_TAG::BUTTON_RIGHT);
				but->setOpacity(200);
				break;
			default:
				break;
			}
		});
		_button_right->setPosition(Vec2(210, 130));
		this->addChild(_button_right, 1);

		//Add Sprite ring
		ringIcon = Sprite::create("Item/ring.png", Rect(200, 48, 64, 50));
		ringIcon->setPosition(Vec2(50, _director->getWinSize().height - ringIcon->getContentSize().height));
		this->addChild(ringIcon, 1);

		//Add label count rings
		countRing = Label::createWithTTF("X  " + std::to_string(mSonic->ringCollected), "fonts/Marker Felt.ttf", 36);
		countRing->setPosition(Vec2(125, _director->getWinSize().height - ringIcon->getContentSize().height));
		this->addChild(countRing, 1);
		this->scheduleUpdate();
};