#pragma once
#include "cocos2d.h"
#include "Sonic.h"
#include "ui/CocosGUI.h"
using namespace cocos2d;
using namespace ui;

class MyUI:public Layer
{
public:
	MyUI() {};
	Sonic* mySonic;
	Button *x_button, *button_rect,*button_trian, *button_cir;
	Sprite* ringIcon;
	Label* countRing;

	void update(float dt)
	{
		countRing->setString("X  " + std::to_string(mySonic->ringCollected));
	}

	MyUI (Sonic* mSonic)
	{
		mySonic = mSonic;
		x_button = Button::create("Button/button_x.png");
		x_button->setScale(0.5);
		x_button->setOpacity(200);
		x_button->addTouchEventListener([this](Ref* sender, Widget::TouchEventType type) {
			auto but = (Button*)sender;
			switch (type)
			{
			case ui::Widget::TouchEventType::BEGAN:
				but->setOpacity(255);
				break;
			case ui::Widget::TouchEventType::ENDED:
				but->setOpacity(200);
				mySonic->mJustTap = BUTTON_TAG::X;
				break;
			default:
				break;
			}
		});
		x_button->setPosition(Vec2(100, 50));
		this->addChild(x_button, 1);

		 button_rect = Button::create("Button/button_rect.png");
		button_rect->setScale(0.5);
		button_rect->setOpacity(200);
		button_rect->addTouchEventListener([this](Ref* sender, Widget::TouchEventType type) {
			auto but = (Button*)sender;
			switch (type)
			{
			case ui::Widget::TouchEventType::BEGAN:
				but->setOpacity(255);
				break;
			case ui::Widget::TouchEventType::ENDED:
				but->setOpacity(200);
				mySonic->mJustTap = BUTTON_TAG::Rectangcle;
				break;
			default:
				break;
			}
		});
		button_rect->setPosition(Vec2(50, 100));
		this->addChild(button_rect, 1);


		 button_trian = Button::create("Button/button_trian.png");
		button_trian->setScale(0.5);
		button_trian->setOpacity(200);
		button_trian->addTouchEventListener([this](Ref* sender, Widget::TouchEventType type) {
			auto but = (Button*)sender;
			switch (type)
			{
			case ui::Widget::TouchEventType::BEGAN:
				but->setOpacity(255);
				break;
			case ui::Widget::TouchEventType::ENDED:
				but->setOpacity(200);
				mySonic->mJustTap = BUTTON_TAG::Tri;
				break;
			default:
				break;
			}
		});
		button_trian->setPosition(Vec2(100, 150));
		this->addChild(button_trian, 1);


		 button_cir = Button::create("Button/button_cir.png");
		button_cir->setScale(0.5);
		button_cir->setOpacity(200);
		button_cir->addTouchEventListener([this](Ref* sender, Widget::TouchEventType type) {
			auto but = (Button*)sender;
			switch (type)
			{
			case ui::Widget::TouchEventType::BEGAN:
				but->setOpacity(255);
				break;
			case ui::Widget::TouchEventType::ENDED:
				mySonic->mJustTap = BUTTON_TAG::Cir;
				but->setOpacity(200);
				break;
			default:
				break;
			}
		});
		button_cir->setPosition(Vec2(150, 100));
		this->addChild(button_cir, 1);

		//Add Sprite ring
		 ringIcon = Sprite::create("ring.png",Rect(200,48,64,50));
		ringIcon->setPosition(50, 975);
		this->addChild(ringIcon, 1);

		//Add label count rings
		 countRing = Label::createWithTTF("X  " + std::to_string(mSonic->ringCollected), "fonts/Marker Felt.ttf", 36);
		countRing->setPosition(125, 975);
		this->addChild(countRing, 1);
		this->scheduleUpdate();
		this->scheduleUpdate();
	};
};