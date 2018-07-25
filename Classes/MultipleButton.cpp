#include "MultipleButton.h"



MultipleButton::MultipleButton()
{
}

MultipleButton::MultipleButton(Vec2 pos, Sonic* sonic, Layer* layer,int button_count, float time)
{
	_mSonic = sonic;
	
	_progressbar =  Sprite::create("GameComponents/progress.png");
	_progressbar->setAnchorPoint(Vec2(0, 0.5f));
	_progressbar->setScale(0.3, 0.3);

	_border=  Sprite::create("GameComponents/border.png");
	_border->setPosition(0, 50);
	_border->setAnchorPoint(Vec2(0, 0.5f));
	_border->setScale(0.3, 0.3);
	this->addChild(_border);

	

	_break_left_Ani= new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(loadAnim("Button/button_break.xml", "blue_left_break"), 0.1f)));
	_break_right_Ani = new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(loadAnim("Button/button_break.xml", "blue_right_break"), 0.1f)));
	
	_button_count = button_count;
	_time = time;

	int pos_x=0;
	int delta_x = _border->getContentSize().width*0.3/(_button_count-1);

	for (int i = 0; i < _button_count; i++)
	{
		int a = 0;
		a=RandomHelper::random_int(1,2);
		Sprite* button;
	
		switch (a)
		{
		case 1:button = Sprite::create(Define::button_left_blue_path); break;
			case 2:button = Sprite::create(Define::button_right_blue_path); break;
		}
		_list_button_sprite.pushBack(button);
		_list_button_tag.push_back(a);


		button->setScale(0.3);
		button->setPosition(pos_x, 0);
		pos_x +=delta_x;
		this->addChild(button);

	}
	mouseBar = ProgressTimer::create(_progressbar);
	mouseBar->setScale(0.3);
	mouseBar->setType(ProgressTimerType::BAR);
	mouseBar->setAnchorPoint(Vec2(0.0, 0.5));
	mouseBar->setBarChangeRate(Vec2(1, 0));
	mouseBar->setMidpoint(Vec2(0.0, 0.0));
	mouseBar->setReverseDirection(true);
	mouseBar->setPercentage(0);
	this->addChild(mouseBar, 10);
	mouseBar->setPosition(0, 47);

	this->scheduleUpdate();

	this->setPosition(pos);
	layer->addChild(this);

	_label = Label::createWithTTF("", "fonts/INVASION2000.TTF", 50);
	_label->enableOutline(Color4B::BLACK, 3);
	_label->setAnchorPoint(Vec2(0.0, 0.5));
	_label->setVisible(false);
	_label->setPosition(0, 50);
	this->addChild(_label, 2);
//	this->autorelease();
}

void MultipleButton::update(float dt)
{
	if (isDelete) return;
	if (this->getPosition().x - _mSonic->getPosition().x <= 800 && !isActive && canActive)
		this->Active();
	/*if (isActive && _mSonic->_list_just_tap.size()>0)
	{
		for (int i = 0; i <  _mSonic->_list_just_tap.size(); i++)
		{
			if (_mSonic->_list_just_tap.at(i) != _list_button_tag.at(i))
			{
				DeleteNow(false);
			}
			else
			{
				if (_list_button_tag.at(i) == 1)
					_list_button_sprite.at(i)->initWithFile(Define::button_left_green_path);
				else
					_list_button_sprite.at(i)->initWithFile(Define::button_right_green_path);
				if (i == _list_button_tag.size() - 1) 
					DeleteNow(true);
			}
		
		}
		
	}*/
	/*if (isActive)
	{
		count_to_auto_play++;
		int i = count_to_auto_play / 20;
		if (i<3)
		{
			
			if (_list_button_tag.at(i) == 1)
				_list_button_sprite.at(i)->initWithFile(Define::button_left_green_path);
			else
				_list_button_sprite.at(i)->initWithFile(Define::button_right_green_path);
			if (i == 2) DeleteNow(true);
		}

	}*/
		
}


void MultipleButton::ActiveButton(BUTTON_TAG dir)
{
	if (_list_button_tag.at(current_button) != dir)
		DeleteNow(false);
	else
	{
		if (_list_button_tag.at(current_button) == 1)
			_list_button_sprite.at(current_button)->initWithFile(Define::button_left_green_path);
		else
			_list_button_sprite.at(current_button)->initWithFile(Define::button_right_green_path);
		current_button++;
		if (current_button == _list_button_tag.size())
			DeleteNow(true);
	}

}

void MultipleButton::Active()
{
	//DeleteNow(true);
	_mSonic->mCurrentButton = this;
	_mSonic->isInMultipleButton = true;
	isActive = true;
	mouseBar->runAction(Sequence::create(ProgressTo::create(1.4f, 83.0f), CallFuncN::create(CC_CALLBACK_0(MultipleButton::BlinkProgressBar, this)), nullptr));
}

void MultipleButton::DeleteNow(bool check)
{
	_mSonic->mCurrentButton = nullptr;
	_mSonic->isInMultipleButton = false;
	isDelete = true;
	if (check)
	{
		isTrue = true;
		auto _green_line = Sprite::create("GameComponents/green_line.png");
		_green_line->setPosition(0, 0);
		_green_line->setAnchorPoint(Vec2(0, 0.5));

		auto line= ProgressTimer::create(_green_line);
		line->setType(ProgressTimerType::BAR);
		line->setAnchorPoint(Vec2(0.0, 0.5));
		line->setBarChangeRate(Vec2(1, 0));
		line->setMidpoint(Vec2(0.0, 0.0));
		line->setPercentage(0);
		this->addChild(line,-1);

		line->runAction(ProgressTo::create(0.3f, 100.0f));
		_mSonic->SetStateByTag(SonicState::ROLL);
		this->runAction(Sequence::create(DelayTime::create(0.6f), RemoveSelf::create(), nullptr));
		
		_mSonic->countCombo += _button_count;
		isCountCombo = true;
		CheckLabel(mouseBar->getPercentage());
	}
	else
	{
		for (int i=0;i<_list_button_sprite.size();i++)
		{
			if (_list_button_tag.at(i) == 1)
			{
				_list_button_sprite.at(i)->runAction(_break_left_Ani->get()->clone());
			}
			else
			{
				_list_button_sprite.at(i)->runAction(_break_right_Ani->get()->clone());
			}
		}
		this->runAction(Sequence::create(DelayTime::create(1), RemoveSelf::create(),nullptr));
		isTrue = false;
	}

	if (!isCountCombo) 
		_mSonic->countCombo = 0;
}

void MultipleButton::BlinkProgressBar()
{
	if (isDelete) return;
	mouseBar->runAction(ProgressTo::create(0.3, 100.0f));
	mouseBar->runAction(Sequence::create(Blink::create(0.7, 8), CallFuncN::create(CC_CALLBACK_0(MultipleButton::DeleteNow, this,false)),nullptr));

}

MultipleButton::~MultipleButton()
{
}

void MultipleButton::CheckLabel(float percen)
{
	_label->setVisible(true);
	_border->setVisible(false);
	mouseBar->setVisible(false);
	if (percen < 40)
	{
		_label->setColor(Color3B(255, 0, 128));
		_label->setString("Perfect!");
		_mSonic->score += 300 * _button_count * _mSonic->scoreMul;
		_mSonic->countPerfect++;
	}
	else if (percen > 40 && percen < 70)
	{
		_label->setColor(Color3B(0, 255, 255));
		_label->setString("Great!");
		_mSonic->score += 200 * _button_count * _mSonic->scoreMul;
		_mSonic->countGreat++;
	}
	else
	{
		_label->setColor(Color3B(255, 128, 0));
		_label->setString("Bad!");
		_mSonic->score += 100 * _button_count * _mSonic->scoreMul;
		_mSonic->countBad++;
	}
	_label->setScale(2);
	auto shake = Repeat::create(
		Sequence::create(
			MoveBy::create(0.08f, Vec2(20, 0)),
			MoveBy::create(0.08f, Vec2(-20, 0)),
			MoveBy::create(0.012f, Vec2(0, 10)),
			MoveBy::create(0.012f, Vec2(0, -10)),
			nullptr), 2);

	_label->runAction(Sequence::create(ScaleTo::create(0.3, 1), shake, nullptr));
}
