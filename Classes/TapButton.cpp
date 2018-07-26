#include "TapButton.h"
using namespace Define;


TapButton::TapButton(Vec2 pos, Sonic* sprite, Layer* layer)
{
	isLeft = RandomHelper::random_int(1, 2);
	mTag =(BUTTON_TAG) isLeft;
	this->initWithFile("Button/unknow.png");
	this->setPosition(pos);


	this->setScale(0.3);

	mTarget = sprite;
	this->scheduleUpdate();
	layer->addChild(this);


	_progressbar = Sprite::create("GameComponents/progress.png");
	_progressbar->setAnchorPoint(Vec2(0.5, 0));

	_border = Sprite::create("GameComponents/border.png");
	_border->setPosition(this->getContentSize()*0.3 + Size(0,150));
	_border->setAnchorPoint(Vec2(0.5, 0));
	_border->setVisible(false);
	this->addChild(_border);

	_label = Label::createWithTTF("", "fonts/INVASION2000.TTF", 130);
	_label->setAnchorPoint(Vec2(0.5f, 0));
	_label->setVisible(false);
	_label->enableOutline(Color4B::BLACK, 5);
	_label->setPosition(this->getContentSize()*0.3 + Size(0, 150));
	this->addChild(_label, 2);

	mouseBar = ProgressTimer::create(_progressbar);
	mouseBar->setType(ProgressTimerType::BAR);
	mouseBar->setAnchorPoint(Vec2(0.5, 0));
	mouseBar->setBarChangeRate(Vec2(1, 0));
	mouseBar->setMidpoint(Vec2(0.0, 0.0));
	mouseBar->setReverseDirection(true);
	mouseBar->setPercentage(0);
	this->addChild(mouseBar, 10);
	mouseBar->setPosition(this->getContentSize()*0.3 + Size(0,150));
//	this->autorelease();
}

TapButton::TapButton(Vec2 pos, Sonic * sprite, Layer * layer, bool isLeft)
{
	//TapButton(pos, sprite, layer);
	this->initWithFile("Button/unknow.png");
	this->setPosition(pos);


	this->setScale(0.3);

	mTarget = sprite;
	this->scheduleUpdate();
	layer->addChild(this);


	_progressbar = Sprite::create("GameComponents/progress.png");
	_progressbar->setAnchorPoint(Vec2(0.5, 0));

	_border = Sprite::create("GameComponents/border.png");
	_border->setPosition(this->getContentSize()*0.3 + Size(0, 150));
	_border->setAnchorPoint(Vec2(0.5, 0));
	_border->setVisible(false);
	this->addChild(_border);

	_label = Label::createWithTTF("", "fonts/INVASION2000.TTF", 130);
	_label->setAnchorPoint(Vec2(0.5f, 0));
	_label->setVisible(false);
	_label->enableOutline(Color4B::BLACK, 5);
	_label->setPosition(this->getContentSize()*0.3 + Size(0, 150));
	this->addChild(_label, 2);

	mouseBar = ProgressTimer::create(_progressbar);
	mouseBar->setType(ProgressTimerType::BAR);
	mouseBar->setAnchorPoint(Vec2(0.5, 0));
	mouseBar->setBarChangeRate(Vec2(1, 0));
	mouseBar->setMidpoint(Vec2(0.0, 0.0));
	mouseBar->setReverseDirection(true);
	mouseBar->setPercentage(0);
	this->addChild(mouseBar, 10);
	mouseBar->setPosition(this->getContentSize()*0.3 + Size(0, 150));
	
	if (isLeft)
		mTag = BUTTON_LEFT;
	else mTag = BUTTON_RIGHT;
}


void TapButton::ActiveButton(BUTTON_TAG dir)
{
	if (isDelete || isTrue) return;
	if (dir == mTag)
	{
		//DeleteNow(true);
		CheckLabel(mouseBar->getPercentage());
		isTrue = true;
		SimpleAudioEngine::getInstance()->playEffect(Define::_music_combo_effect_path);
		if (isLeft == 1)
			this->initWithFile(Define::button_left_green_path);
		else
			this->initWithFile(Define::button_right_green_path);
		if (this->getPositionX() - mTarget->getPositionX()>300)
			mTarget->SetStateByTag(SonicState::RUNSKIP);
	}
	else 
		DeleteNow(false);
}

TapButton::~TapButton()
{
}

void TapButton::CheckLabel(float percen)
{
	_label->setVisible(true);
	_border->setVisible(false);
	mouseBar->setVisible(false);
	if (percen < 30)
	{
		_label->setColor(Color3B(255, 0, 128));
		_label->setString("Perfect!");
		score = PERFECT;
		mTarget->score += 300 * mTarget->scoreMul;
		mTarget->countPerfect++;
	}
	else if (percen > 30 && percen < 70)
	{
		_label->setColor(Color3B(0,255,255));
		_label->setString("Great!");
		score = GREAT;
		mTarget->score += 200 * mTarget->scoreMul;
		mTarget->countGreat++;
	}
	else
	{
		_label->setColor(Color3B(255,128,0));
		_label->setString("Bad!");
		score = BAD;
		mTarget->score += 100 * mTarget->scoreMul;
		mTarget->countBad++;
	}
	_label->setScale(2);
	auto shake= Repeat::create(
		Sequence::create(
			MoveBy::create(0.08f, Vec2(20, 0)),
			MoveBy::create(0.08f, Vec2(-20, 0)),
			MoveBy::create(0.012f, Vec2(0, 10)),
			MoveBy::create(0.012f, Vec2(0, -10)),
			nullptr), 2);

	_label->runAction(Sequence::create(ScaleTo::create(0.3,1),shake,nullptr));
}

void TapButton::SetCanActive(bool is)
{

	if (is == canActive) return;
	canActive = is;
	if (isActive)
	{
		mTarget->mCurrentButton = this;
		_border->setVisible(true);
		auto func = CallFunc::create([this]()
		{
			if (isDelete) return;
			mouseBar->runAction(Spawn::create(Blink::create(0.7, 8),ProgressTo::create(0.3, 100.0f),nullptr));
			
		});
		mouseBar->runAction(Sequence::create(ProgressTo::create(time, 83.0f), func, nullptr));
		switch (mTag)
		{
		case BUTTON_RIGHT:
			this->initWithFile(Define::button_right_blue_path);
			_break_Ani = new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(loadAnim("Button/button_break.xml", "blue_right_break"), 0.1f)));
			break;

		case BUTTON_LEFT:
			this->initWithFile(Define::button_left_blue_path);
			_break_Ani = new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(loadAnim("Button/button_break.xml", "blue_left_break"), 0.1f))); break;

		default:
			break;
		}
	}
}

void TapButton::Active()
{	
	isActive = true;
	if (canActive)
	{
		mTarget->mCurrentButton = this;
		auto func = CallFunc::create([this]()
		{
			if (isDelete) return;
			mouseBar->runAction(Spawn::create(Blink::create(0.7, 8), ProgressTo::create(0.3, 100.0f), nullptr));

		});
		mouseBar->runAction(Sequence::create(ProgressTo::create(time, 83.0f), func, nullptr));
		_border->setVisible(true);
		switch (mTag)
		{
		case BUTTON_RIGHT:
			this->initWithFile(Define::button_right_blue_path);
			_break_Ani = new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(loadAnim("Button/button_break.xml", "blue_right_break"), 0.1f)));
			break;

		case BUTTON_LEFT:
			this->initWithFile(Define::button_left_blue_path);
			_break_Ani = new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(loadAnim("Button/button_break.xml", "blue_left_break"), 0.1f))); break;

		default:
			break;
		}
	}

}


void TapButton::DeleteNow(bool check)
{
	mTarget->mCurrentButton = nullptr;
	_border->runAction(RemoveSelf::create());
	_progressbar->runAction(RemoveSelf::create());
	mouseBar->runAction(RemoveSelf::create());


	isDelete = true;
	if (check)
	{
		isTrue = true;
		this->runAction(RemoveSelf::create());
		mTarget->countCombo++;
		isCountCombo = true;
	}
	else
	{
		isTrue = false;
		//this->setScale(0.15);
		if(_break_Ani!=nullptr)
		this->runAction(Sequence::create(_break_Ani->get(), RemoveSelf::create(), nullptr));
		if (!isCountCombo) mTarget->countCombo = 0;
	}
}


void TapButton::update(float dt)
{
	


	if (isDelete) return;
	if (this->getPositionX() < mTarget->getPositionX() && !use_for_Hold) 
		DeleteNow(false);
	if (this->getPosition().x - mTarget->getPosition().x <= 600 && !isActive && !use_for_Hold)
		this->Active();
	if (isActive && canActive)
	{
		
		if (isTrue && use_for_Hold)
		{
			mTarget->getPhysicsBody()->setGravityEnable(true);
			mTarget->SetVelocityX(0);
			mTarget->SetStateByTag(_action);
			DeleteNow(true);
			return;
		}
		
		//DeleteNow(true);
			//mTarget->SetStateByTag(_action);
		/*	DeleteNow(true);
			return;*/
		

		//BUTTON_TAG tag = mTarget->mJustTap;
		//tag = mTag;

		/*if (tag != NONE && tag != mTag)
		{
			DeleteNow(false);
			return;
		}*/

		if (isTrue &&  this->getPositionX() - mTarget->getPositionX() <= 10)
		{
			mTarget->SetVelocityX(0);
			mTarget->SetStateByTag(_action);
			DeleteNow(true);
			return;
		}
	}
}
