#include "TapButton.h"



TapButton::TapButton(int ID,Vec2 pos,Sprite* sprite, Layer* layer)
{
	switch (ID)
	{
	case 1:
		this->initWithFile("Button/button_x.png");
		break;
	case 2:this->initWithFile("Button/button_rect.png"); break;
	case 3:this->initWithFile("Button/button_trian.png"); break;
	case 4:this->initWithFile("Button/button_cir.png");  break;
	default:
		break;
	}

	circle = Sprite::create("Button/circle.png");
	circle->setAnchorPoint(Vec2(0.5, 0.5));
	this->setAnchorPoint(Vec2(0.5, 0.5));
	circle->setPosition(pos);
	this->setPosition(pos);


	this->setScale(0.3);
	circle->setScale(0.3);


	mTarget = sprite;
	this->scheduleUpdate();
	layer->addChild(this);
	layer->addChild(circle,-1);
}


TapButton::~TapButton()
{
}

void TapButton::Active()
{	

	circle->runAction(ScaleTo::create(10, 0));
	isActive = true;
}

void TapButton::update(float dt)
{
	if (this->getPosition().x - mTarget->getPosition().x <= 600 && !isActive)
		this->Active();
	
}
