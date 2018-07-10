#include "ComboScore.h"

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
		_label->setScale(1.15);
	}
	else if (x >= 20 && x < 25)
	{
		_label->setColor(Color3B(255, 0, 0));
		_label->setScale(1.2);
	}
	_label->enableOutline(Color4B::BLACK, 3);
}

void ComboScore::UpdateCombo()
{	
	_mySonic->countCombo++;
	CreateEffect();
	Evaluate();
}

void ComboScore::ResetCombo()
{
	_mySonic->countCombo = 0;
	_label->stopAllActions();
	_label->runAction(FadeOut::create(0));
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
	_label->setPosition(Vec2(110, 0.875 * _director->getWinSize().height));
	_label->setRotation(-15);

	//auto delayTime = DelayTime::create(2);
	//auto fadeOut = FadeOut::create(0.1);

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
	if (x != 0 && x % 5 == 0 && x <= 20) 
	{
		_label2->stopAllActions();
		_label2->setVisible(true);
		_label2->setPosition(_mySonic->getContentSize().width / 2, _mySonic->getContentSize().height / 2 + 100);
		switch (x) 
		{
		case 5:
			_label2->setString("Cool!");
			_label2->setColor(Color3B(255, 255, 0));
			break;
		case 10:
			_label2->setString("Good!");
			_label2->setColor(Color3B(255, 128, 0));
			break;
		case 15:
			_label2->setString("Excellent!");
			_label2->setColor(Color3B(102, 102, 255));
			break;
		case 20:
			_label2->setString("Perfect!");
			_label2->setColor(Color3B(255, 0, 0));
			break;
		default:
			break;
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
	

