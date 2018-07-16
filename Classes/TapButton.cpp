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

	this->setPosition(pos);


	this->setScale(0.3);

	mTarget = sprite;
	this->scheduleUpdate();
	layer->addChild(this);

}


TapButton::~TapButton()
{
}

void TapButton::Active()
{	
	isActive = true;
}

void TapButton::Dissapear()
{
	
	auto fadeOut = FadeOut::create(0.1f);
	auto reverse = fadeOut->reverse();
	ActionInterval *fade = Sequence::create(fadeOut, reverse, nullptr);
	auto fading = Repeat::create(fade, _time_dissapear / 0.1);
	auto actionMoveDone = CallFuncN::create(CC_CALLBACK_0(TapButton::DeleteNow, this, false));
	this->runAction(Sequence::create(fading, actionMoveDone, NULL));
}

void TapButton::DeleteNow(bool check)
{
	
	isDelete = true;
	mTarget->mJustTap = NONE;
	if (check)
	{
	
		this->runAction(Sequence::create(DelayTime::create(0.7), RemoveSelf::create(),nullptr));
		mTarget->countCombo++;
		isCountCombo = true;
	}
	else
	{
		this->setScale(0.15);
		this->runAction(Sequence::create(_break_Ani->get(), RemoveSelf::create(), nullptr));
		if (!isCountCombo) mTarget->countCombo = 0;
	}
}


void TapButton::update(float dt)
{
	


	if (isDelete) return;
	if (this->getPosition().x - mTarget->getPosition().x <= 600 && !isActive)
		this->Active();
	if (isActive && isFirst)
	{
	/*	if (can_Active)
		{
			mTarget->SetStateByTag(_action);
			DeleteNow(true);
			return;
		}*/

		BUTTON_TAG tag = mTarget->mJustTap;
	
		if (tag != NONE && tag != mTag)
		{
			DeleteNow(false);
			return;
		}

		if (tag == mTag && !isTrue)
		{
			isTrue = true;
			if (isLeft == 1)
				this->initWithFile(Define::button_left_green_path);
			else
				this->initWithFile(Define::button_right_green_path);
		}

		if (isTrue &&  this->getPositionX() - mTarget->getPositionX() <= 10)
		{
			mTarget->SetStateByTag(_action);
			DeleteNow(true);
			return;
		}
	}
}
