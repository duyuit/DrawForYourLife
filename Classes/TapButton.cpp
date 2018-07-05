#include "TapButton.h"
using namespace Define;


TapButton::TapButton(int ID,Vec2 pos, Sonic* sprite, Layer* layer)
{
	switch (ID)
	{
	case 1:
		this->initWithFile("Button/button_x.png");
		_break_Ani= new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(loadAnim("Button/button_break.xml","x"), 0.1f)));
		mTag =BUTTON_TAG::X;
		break;
	case 2:this->initWithFile("Button/button_rect.png");
		mTag = BUTTON_TAG::Rectangcle; 
		_break_Ani = new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(loadAnim("Button/button_break.xml", "rect"), 0.1f)));
		break;
	case 3:this->initWithFile("Button/button_trian.png");
		mTag = BUTTON_TAG::Tri; 
		_break_Ani = new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(loadAnim("Button/button_break.xml", "tria"), 0.1f)));
		break;
	case 4:this->initWithFile("Button/button_cir.png"); 
		mTag = BUTTON_TAG::Cir; 
		_break_Ani = new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(loadAnim("Button/button_break.xml", "circle"), 0.1f)));
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
	circle->setScale(1.3);

	mTarget = sprite;
	this->scheduleUpdate();
	layer->addChild(this);
	layer->addChild(circle,1);
}


TapButton::~TapButton()
{
}

void TapButton::Active()
{	

	auto actionMoveDone = CallFuncN::create(CC_CALLBACK_0(TapButton::Dissapear, this));

	circle->runAction(Sequence::create(ScaleTo::create(1.0, 0.29), actionMoveDone,NULL));

	isActive = true;
}

void TapButton::Dissapear()
{
	can_Active = true;
	auto fadeOut = FadeOut::create(0.1f);
	auto reverse = fadeOut->reverse();
	ActionInterval *fade = Sequence::create(fadeOut, reverse, nullptr);
	auto fading = Repeat::create(fade, time_dissapear/0.1);
	auto actionMoveDone = CallFuncN::create(CC_CALLBACK_0(TapButton::DeleteCircle, this));
	this->runAction(Sequence::create(fading, RemoveSelf::create(), actionMoveDone, NULL));
}

void TapButton::DeleteNow(bool check)
{
	DeleteCircle();
	isDelete = true;
	mTarget->mJustTap = NONE;
	if(check)
		this->runAction(RemoveSelf::create());
	else
		this->runAction(Sequence::create(_break_Ani->get(),RemoveSelf::create(),nullptr));
}

void TapButton::DeleteCircle()
{
	if (circle != nullptr)
	{
		this->circle->runAction(RemoveSelf::create());
		this->circle = nullptr;
	}

}

void TapButton::update(float dt)
{
	if (isDelete) return;
	if (this->getPosition().x - mTarget->getPosition().x <= 600 && !isActive)
		this->Active();
	if (isActive && isFirst)
	{
		if (can_Active)
		{
			mTarget->SetStateByTag(SonicState::StateAction::JUMP);
			DeleteNow(false);
			return;
		}

		BUTTON_TAG tag = mTarget->mJustTap;
		if (!can_Active && tag != NONE)
		{
			DeleteNow(false);
			return;
		}
		if (tag != NONE && tag != mTag)
		{
			DeleteNow(false);
			return;
		}
		if (this->getPosition().x - mTarget->getPosition().x <= 600 && can_Active)
		{
			if (tag == NONE)
				return;
			if (tag == mTag)
			{
				mTarget->SetStateByTag(SonicState::StateAction::JUMP);
				DeleteNow(true);
				return;
			}
		}
	}
}
