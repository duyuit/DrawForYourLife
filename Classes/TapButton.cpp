#include "TapButton.h"
using namespace Define;


TapButton::TapButton(Vec2 pos, Sonic* sprite, Layer* layer)
{
	isLeft = RandomHelper::random_int(1, 2);
	switch (isLeft)
	{
	case 2:
		this->initWithFile(Define::button_right_grey_path);
		_break_Ani = new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(loadAnim("Button/button_break.xml", "right_break"), 0.1f)));
		mTag = BUTTON_TAG::BUTTON_RIGHT;
		break;
		
	case 1:
		this->initWithFile(Define::button_left_grey_path);
		mTag = BUTTON_TAG::BUTTON_LEFT;
		_break_Ani = new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(loadAnim("Button/button_break.xml", "left_break"), 0.1f))); break;
	
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

	circle->runAction(Sequence::create(ScaleTo::create(_time_circle_shrink, 0.29), actionMoveDone,NULL));

	isActive = true;
}

void TapButton::Dissapear()
{
	can_Active = true;
	auto fadeOut = FadeOut::create(0.1f);
	auto reverse = fadeOut->reverse();
	ActionInterval *fade = Sequence::create(fadeOut, reverse, nullptr);
	auto fading = Repeat::create(fade, _time_dissapear / 0.1);
	auto actionMoveDone = CallFuncN::create(CC_CALLBACK_0(TapButton::DeleteNow, this, false));
	this->runAction(Sequence::create(fading, actionMoveDone, NULL));
}

void TapButton::DeleteNow(bool check)
{
	DeleteCircle();
	isDelete = true;
	mTarget->mJustTap = NONE;
	if (check)
	{
		if (isLeft == 1)
			this->initWithFile(Define::button_left_green_path);
		else
			this->initWithFile(Define::button_right_green_path);
		this->runAction(Sequence::create(DelayTime::create(0.7), RemoveSelf::create(),nullptr));
	}
	else
	{
		this->setScale(0.15);
		this->runAction(Sequence::create(_break_Ani->get(), RemoveSelf::create(), nullptr));
	}
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
	if(circle)
	circle->setPosition(this->getPosition());


	if (isDelete) return;
	if (this->getPosition().x - mTarget->getPosition().x <= 600 && !isActive)
		this->Active();
	if (isActive && isFirst)
	{
		/*if (can_Active)
		{
			mTarget->SetStateByTag(_action);
			DeleteNow(true);
			return;
		}*/

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
				mTarget->SetStateByTag(_action);
				DeleteNow(true);
				return;
			}
		}
	}
}
