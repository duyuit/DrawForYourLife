#include "TapButton.h"



TapButton::TapButton(int ID,Vec2 pos, Sonic* sprite, Layer* layer)
{
	switch (ID)
	{
	case 1:
		this->initWithFile("Button/button_x.png");
		mTag =BUTTON_TAG::X;
		break;
	case 2:this->initWithFile("Button/button_rect.png");
		mTag = BUTTON_TAG::Rectangcle; 
		break;
	case 3:this->initWithFile("Button/button_trian.png");
		mTag = BUTTON_TAG::Tri; 
		break;
	case 4:this->initWithFile("Button/button_cir.png"); 
		mTag = BUTTON_TAG::Cir; 
		break;
	default:
		break;
	}

	circle = Sprite::create("Button/circle.png");
	circle->setAnchorPoint(Vec2(0.5, 0.5));
	this->setAnchorPoint(Vec2(0.5, 0.5));
	circle->setPosition(pos);
	this->setPosition(pos);


	this->setScale(0.3);
	circle->setScale(0.8);

	//circle->setScale(2);

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

	auto actionMoveDone = CallFuncN::create(CC_CALLBACK_0(TapButton::Dissapear, this));

	circle->runAction(Sequence::create(ScaleTo::create(1.0, 0.29), actionMoveDone, RemoveSelf::create(),NULL));

	isActive = true;
}

void TapButton::Dissapear()
{
	can_Active = true;
	auto fadeOut = FadeOut::create(0.1f);
	auto reverse = fadeOut->reverse();
	ActionInterval *fade = Sequence::create(fadeOut, reverse, nullptr);
	auto fading = Repeat::create(fade,3);

	/*auto wait = Sequence::create(DelayTime::create(2.5f), RemoveSelf::create(), NULL);
	auto mySpawn = Spawn::createWithTwoActions(fading, wait);*/


	this->runAction(Sequence::create(fading, RemoveSelf::create(), NULL));
}

void TapButton::update(float dt)
{
	if (this->getPosition().x - mTarget->getPosition().x <= 600 && !isActive)
		this->Active();
	if (isActive)
	{
		BUTTON_TAG tag = mTarget->mJustTap;
		if (tag != NONE && tag != mTag)
		{
			this->circle->runAction(RemoveSelf::create());
			this->runAction(RemoveSelf::create());
			return;
		}
		if (this->getPosition().x - mTarget->getPosition().x <= 600 && can_Active)
		{
		/*	if (tag != NONE && tag != mTag)
			{
				this->runAction(RemoveSelf::create());
				return;
			}*/
			if (tag == NONE) return;
			if (tag == mTag)
			{
				
				mTarget->SetStateByTag(SonicState::StateAction::JUMP);
			//	mTarget->SetStateByTag(SonicState::StateAction::JUMP);
				this->runAction(RemoveSelf::create());
				return;
			}
		}
	}
}
