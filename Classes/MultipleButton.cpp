#include "MultipleButton.h"



MultipleButton::MultipleButton()
{
}

MultipleButton::MultipleButton(Vec2 pos, Sonic* sonic, Layer* layer,int button_count, float time)
{
	_mSonic = sonic;

	_progressbar =  Sprite::create("GameComponents/progress.png");
	_progressbar->setFlipX(true);
	_progressbar->setAnchorPoint(Vec2(0, 0.5f));
	_progressbar->setScale(0.3, 0.3);

	_border=  Sprite::create("GameComponents/border.png");
	_border->setPosition(0, 50);
	_border->setAnchorPoint(Vec2(0, 0.5f));
	_border->setScale(0.3, 0.3);
	this->addChild(_border);

	

	_break_left_Ani= new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(loadAnim("Button/button_break.xml", "left_break"), 0.1f)));
	_break_right_Ani = new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(loadAnim("Button/button_break.xml", "right_break"), 0.1f)));
	
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
		case 1:button = Sprite::create(Define::button_left_grey_path); break;
			case 2:button = Sprite::create(Define::button_right_grey_path); break;
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
	mouseBar->setPosition(0, 50);

	this->scheduleUpdate();

	this->setPosition(pos);
	layer->addChild(this);
}

void MultipleButton::update(float dt)
{
	if (isDelete) return;
	if (this->getPosition().x - _mSonic->getPosition().x <= 800 && !isActive)
		this->Active();
	//if (isActive && _mSonic->_list_just_tap.size()>0)
	//{
	//	for (int i = 0; i <  _mSonic->_list_just_tap.size(); i++)
	//	{
	//		/*if (_mSonic->_list_just_tap.at(i) != _list_button_tag.at(i))
	//		{
	//			DeleteNow(false);
	//		}
	//		else*/
	//		{
	//			if (_list_button_tag.at(i) == 1)
	//				_list_button_sprite.at(i)->initWithFile(Define::button_left_green_path);
	//			else
	//				_list_button_sprite.at(i)->initWithFile(Define::button_right_green_path);
	//			if (i == _list_button_tag.size() - 1) DeleteNow(true);
	//		}
	//	
	//	}
	//	
	//}
	if (isActive)
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
	}
		
}


void MultipleButton::Active()
{
	isActive = true;
	_mSonic->_list_just_tap.clear();
	mouseBar->runAction(Sequence::create(ProgressTo::create(1.3f, 70.0f), CallFuncN::create(CC_CALLBACK_0(MultipleButton::BlinkProgressBar, this)), nullptr));
}

void MultipleButton::DeleteNow(bool check)
{
	isDelete = true;
	if (check)
	{
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
	}
	else
	{
			
		for (int i=0;i<_list_button_sprite.size();i++)
		{
			_list_button_sprite.at(i)->setScale(0.15);
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

		if (!isCountCombo) _mSonic->countCombo = 0;

	}

}

void MultipleButton::BlinkProgressBar()
{
	if (isDelete) return;
	mouseBar->runAction(ProgressTo::create(0.7, 100.0f));
	mouseBar->runAction(Sequence::create(Blink::create(0.7, 8), CallFuncN::create(CC_CALLBACK_0(MultipleButton::DeleteNow, this,false)),nullptr));

}

MultipleButton::~MultipleButton()
{
}
