#include "ComboScore.h"

ComboScore::ComboScore(Sonic* mSonic) {
	_mySonic = mSonic;

	//_sprite = Sprite::create("label-ring-bg.png");
	//_sprite->setAnchorPoint(Vec2(0.5f, 0.5f));
	//_sprite->setVisible(false);
	//this->addChild(_sprite, 1);

	_label = Label::createWithTTF("", "fonts/PixelGameFont.ttf", 24);
	_label->setAnchorPoint(Vec2(0.5f, 0.5f));
	_label->setVisible(false);
	this->addChild(_label, 1);

	_label2 = Label::createWithTTF("", "fonts/INVASION2000.TTF", 48);
	_label2->setAnchorPoint(Vec2(0.5f, 0.5f));
	_label2->setVisible(false);
	_mySonic->addChild(_label2, 100);

	this->scheduleUpdate();
}

void ComboScore::SetColor()
{
	int x = _mySonic->countCombo;
	if (x >= 0 && x < 5) {
		_label->setColor(Color3B(255, 255, 255));
		_label->setScale(1);
	}
	else if (x >= 5 && x < 10)
	{
		_label->setColor(Color3B(255, 255, 0));
		_label->setScale(1.05);
	}
	else if (x >= 10 && x < 15)
	{
		_label->setColor(Color3B(255, 128, 0));
		_label->setScale(1.1);
	}
	else if (x >= 15 && x < 20)
	{
		_label->setColor(Color3B(102, 102, 255));
		_label->setScale(1.2);
	}
	else if (x >= 20)
	{
		_label->setColor(Color3B(255, 0, 0));
		_label->setScale(1.3);
	}
	_label->enableOutline(Color4B::BLACK, 3);
}

void ComboScore::UpdateCombo()
{	
	CreateEffect();
	Evaluate();
	 
}

void ComboScore::ResetCombo()
{
	_label->stopAllActions();
	_label->setVisible(false);

	_label2->stopAllActions();
	_label2->setVisible(false);

	isCool = isGood = isExcellent = isPerfect = false;
	_label2->setString("");
}

void ComboScore::CreateEffect()
{
	_label->stopAllActions();
	_label->setVisible(true);
	//_sprite->setVisible(true);
	//_sprite->setScale(0.5, 0.3);
	//_sprite->setPosition(Vec2(110, 0.875 * _director->getWinSize().height));
	//_sprite->setRotation(-15);

	_label->setString("X " + std::to_string(_mySonic->countCombo) + " COMBO");
	_label->setPosition(Vec2(110, _director->getWinSize().height - _mySonic->getContentSize().height));
	_label->setRotation(-15);

	_label->runAction(FadeIn::create(0.1));

	_label->runAction(
		Repeat::create(
			Sequence::create(
				MoveBy::create(0.05f, Vec2(12, 0)),
				MoveBy::create(0.05f, Vec2(-12, 0)),
				MoveBy::create(0.012f, Vec2(0, 3)),
				MoveBy::create(0.012f, Vec2(0, -3)),
				nullptr),2));

	_label->runAction(
		Sequence::create(
			RotateTo::create(0.05f,-15+6), 
			RotateTo::create(0.05f,-15-6), 
			RotateTo::create(0.025f, -15), nullptr));

}

void ComboScore::Evaluate()
{
	int x = _mySonic->countCombo;
	if (x != 0) 
	{
		_label2->stopAllActions();
		_label2->setVisible(true);
		_label2->setPosition(_mySonic->getContentSize().width / 2, _mySonic->getContentSize().height / 2 + 100);
		
		if (x >= 5 && x < 10)
		{
			if (!isCool)
			{		
				_label2->setColor(Color3B(255, 255, 0));
				_label2->setString("Cool!!");
				isCool = true;
			}
			else _label2->setString("");
		}
		else if (x >= 10 && x < 15)
		{
			if (!isGood) 
			{
				_label2->setColor(Color3B(255, 128, 0));
				_label2->setString("Good!");
				isGood = true;
			}
			else _label2->setString("");
		}
		else if (x >= 15 && x < 20)
		{
			if (!isExcellent) 
			{
				_label2->setColor(Color3B(102, 102, 255));
				_label2->setString("Excellent!");
				isExcellent = true;
			}
			else _label2->setString("");
		}
		else if (x >= 20)
		{
			if (!isPerfect)
			{
				_label2->setColor(Color3B(255, 0, 0));
				_label2->setString("Perfect!");
				isPerfect = true;
			}
			else _label2->setString("");
		}
		_label2->enableOutline(Color4B::BLACK, 3);
		
		_label2->runAction(
			Sequence::create(
				FadeIn::create(0.1), 
				MoveBy::create(0.5, Vec2(0, 15)), 
				DelayTime::create(1), 
				FadeOut::create(0.1), nullptr));	
	}
}

void ComboScore::update(float dt)
{
	if (_pre_combo != _mySonic->countCombo)
	{
		if (_mySonic->countCombo == 0)
		{
			ResetCombo();
		}
		else
		{
			SimpleAudioEngine::getInstance()->playEffect(Define::_music_combo_effect_path);
			UpdateCombo();

		}
		SetColor();	
	}
	_pre_combo = _mySonic->countCombo;
}