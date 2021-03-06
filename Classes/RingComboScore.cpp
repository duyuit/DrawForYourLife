#include "RingComboScore.h"

RingComboScore::RingComboScore(Sonic* mSonic) 
{
	this->autorelease();
	_mySonic = mSonic;
	string font = "fonts/hemi.ttf";
	//Add Sprite ring
	_ringIcon = Sprite::create("Item/ring.png", Rect(200, 48, 64, 50));
	_ringIcon->setPosition(Vec2(50, _director->getWinSize().height - _ringIcon->getContentSize().height));
	this->addChild(_ringIcon, 1);

	_distance = mSonic->getContentSize().height;
	_distance2 = _ringIcon->getContentSize().height;

	//Add label count rings
	_countRing = Label::createWithTTF("X  " + std::to_string(mSonic->ringCollected), font, 36);
	_countRing->setAnchorPoint(Vec2(0, 0.5));
	_countRing->setPosition(Vec2(100, _director->getWinSize().height - _distance2));
	_countRing->enableOutline(Color4B::BLACK, 3);
	this->addChild(_countRing, 1);

	//Add label combo
	_xCombo = Label::createWithTTF("", font, 32);
	_xCombo->setAnchorPoint(Vec2(0.5f, 0.5f));
	_xCombo->setVisible(false);
	this->addChild(_xCombo, 1);

	//Add label combo 2
	_xCombo2 = Label::createWithTTF("", font, 32);
	_xCombo2->setAnchorPoint(Vec2(0.5f, 0.5f));
	_xCombo2->setVisible(false);
	this->addChild(_xCombo2, 1);

	//Add label: Cool - Good - Excellent - Perfect
	_evaluate = Label::createWithTTF("", font, 60);
	_evaluate->setAnchorPoint(Vec2(0.5f, 0.5f));
	_evaluate->setVisible(false);
	_mySonic->addChild(_evaluate, 100);

	//Add label score
	_score = Label::createWithTTF("Score: " + std::to_string(_mySonic->score), font, 36);
	_score->setAnchorPoint(Vec2(0.0f, 0.5f));
	_score->setPosition(Vec2(_director->getWinSize().width - 7.5 * _distance2, _director->getWinSize().height - _distance2));
	_score->enableOutline(Color4B::BLACK, 3);
	this->addChild(_score, 1);

	//Add label plus score
	_plusScore = Label::createWithTTF("+ " + std::to_string(_mySonic->score), font, 24);
	_plusScore->setAnchorPoint(Vec2(0.0f, 0.5f));
	_plusScore->setPosition(_director->getWinSize().width - 4 * _distance2, _director->getWinSize().height - 2.2 * _distance2);
	_plusScore->enableOutline(Color4B::BLACK, 3);
	_plusScore->setVisible(false);
	this->addChild(_plusScore, 1);

	//Add flame effect
	flame = Sprite::create();
	flame->setAnchorPoint(Vec2(0.5, 0));
	flame->setScale(1.5, 0.875);
	flame_FL = Define::loadAnim("Particle/flame_combo.xml", "1");
	flame_Ani = new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(flame_FL, 0.06f)));
	flame_blue_Ani = new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(Define::loadAnim("Particle/flame_combo_blue.xml", "1"), 0.06f)));
	//flame->runAction(RepeatForever::create(flame_Ani->get()));
	this->addChild(flame, 0);
	//this->autorelease();
	this->scheduleUpdate();
}

void RingComboScore::UpdateCombo()
{
	SetLabel();
	CreateEffect();
	Evaluate();
	_mySonic->maxCombo = MAX(_mySonic->maxCombo, _mySonic->countCombo);
}

void RingComboScore::ResetCombo()
{
	_mySonic->scoreMul = 1.0;
	if (_mySonic->isRed)
	{
		_mySonic->_transform_blue->setVisible(true);
		_mySonic->_transform_blue->runAction(Sequence::create(FadeIn::create(0.1), _mySonic->_transform_blue_Ani->get(), FadeOut::create(0.1), nullptr));
		_mySonic->SwapAllAni();
		_mySonic->isRed = false;
	}

	//Label combo
	_xCombo->stopAllActions();
	_xCombo->setVisible(false);
	_xCombo2->stopAllActions();
	_xCombo2->setVisible(false);

	//Label: Cool - Good - Excellent - Perfect
	_evaluate->stopAllActions();
	_evaluate->setVisible(false);
	_evaluate->setString("");
	isCool = isGood = isExcellent = isPerfect = false;
}

void RingComboScore::SetColor()
{
	int x = _mySonic->countCombo;
	if (x >= 0 && x < 5) {
		_xCombo->setColor(Color3B(255, 255, 255));
		_xCombo2->setColor(Color3B(255, 255, 255));
	}
	else if (x >= 5 && x < 10)
	{
		_xCombo->setColor(Color3B(0, 255, 255));
		_xCombo2->setColor(Color3B(0, 255, 255));		
	}
	else if (x >= 10 && x < 15)
	{
		_xCombo->setColor(Color3B(255, 255, 0));
		_xCombo2->setColor(Color3B(255, 255, 0));
	}
	else if (x >= 15 && x < 20)
	{
		_xCombo->setColor(Color3B(255, 128, 0));
		_xCombo2->setColor(Color3B(255, 128, 0));
	}
	else if (x >= 20)
	{
		_xCombo->setColor(Color3B(255, 0, 0));
		_xCombo2->setColor(Color3B(255, 0, 0));
	}
	_xCombo->enableOutline(Color4B::BLACK, 3);
	_xCombo2->enableOutline(Color4B::BLACK, 3);
}

void RingComboScore::SetLabel()
{
	//Label combo
	_xCombo->stopAllActions();
	_xCombo->setVisible(true);

	_xCombo->setString("COMBO");
	_xCombo->setPosition(Vec2(_director->getWinSize().width / 2, _director->getWinSize().height - 0.6 * _distance));

	//Label combo 2
	_xCombo2->stopAllActions();
	_xCombo2->setVisible(true);

	_xCombo2->setString(std::to_string(_mySonic->countCombo));
	_xCombo2->setPosition(Vec2(_director->getWinSize().width / 2, _director->getWinSize().height - 0.85 *_distance));
	flame->setPosition(_xCombo->getPosition() + Vec2(0, -55));

	//Label score
	_score->setString("Score: " + std::to_string(_mySonic->score));
	_score->setPosition(Vec2(_director->getWinSize().width - 7.5 * _distance2, _director->getWinSize().height - _distance2));

	//Label plus score
	_plusScore->stopAllActions();
	_plusScore->setVisible(true);

	_plusScore->setString("+ " + std::to_string(_delta_score));
	_plusScore->setPosition(_director->getWinSize().width - 4 * _distance2, _director->getWinSize().height - 2.2 * _distance2);
}

void RingComboScore::CreateEffect()
{
	//Label combo
	_xCombo->setScale(2);
	_xCombo->setOpacity(0);
	_xCombo->runAction(Spawn::create(
		ScaleTo::create(0.5, 1),
		FadeTo::create(0.3,220),
		nullptr
	));


	_xCombo->runAction(FadeIn::create(0.1));

	_xCombo->runAction(
		Repeat::create(
			Sequence::create(
				MoveBy::create(0.05f, Vec2(12, 0)),
				MoveBy::create(0.05f, Vec2(-12, 0)),
				MoveBy::create(0.012f, Vec2(0, 3)),
				MoveBy::create(0.012f, Vec2(0, -3)),
				nullptr), 2));

	_xCombo->runAction(
		Sequence::create(
			RotateTo::create(0.05f, 6),
			RotateTo::create(0.05f, -6),
			RotateTo::create(0.025f, 0), nullptr));

	//Label combo 2
	_xCombo2->setScale(3.5);
	_xCombo2->setOpacity(0);

	_xCombo2->runAction(Spawn::create(
		ScaleTo::create(0.5, 1),
		FadeIn::create(0.3),
		nullptr
	));
	_xCombo2->runAction(FadeIn::create(0.1));

	_xCombo2->runAction(
		Repeat::create(
			Sequence::create(
				MoveBy::create(0.05f, Vec2(12, 0)),
				MoveBy::create(0.05f, Vec2(-12, 0)),
				MoveBy::create(0.012f, Vec2(0, 3)),
				MoveBy::create(0.012f, Vec2(0, -3)),
				nullptr), 2));

	_xCombo2->runAction(
		Sequence::create(
			RotateTo::create(0.05f, 6),
			RotateTo::create(0.05f, -6),
			RotateTo::create(0.025f, 0), nullptr));

	//Label plus score
	_plusScore->runAction(FadeIn::create(0.1));
	_plusScore->runAction(
		Sequence::create(
			MoveBy::create(0.5, Vec2(0, 20)),
			DelayTime::create(1),
			FadeOut::create(0.5), nullptr));
}

void RingComboScore::Evaluate()
{
	int x = _mySonic->countCombo;
	if (x != 0)
	{
		_evaluate->stopAllActions();
		_evaluate->setVisible(true);
		_evaluate->setPosition(_mySonic->getContentSize().width / 2, _mySonic->getContentSize().height / 2 + 100);

		if (x >= 5 && x < 10)
		{
			if (!isCool)
			{
				_mySonic->scoreMul = 1.5;
				_evaluate->setColor(Color3B(0, 255, 255));
				//_evaluate->setString("Cool!!");
				isCool = true;
			}
			else _evaluate->setString("");
		}
		else if (x >= 10 && x < 15)
		{
			if (!isGood)
			{
				_mySonic->scoreMul = 2.0;
				_evaluate->setColor(Color3B(255, 255, 0));
				//_evaluate->setString("Good!");
				isGood = true;
			}
			else _evaluate->setString("");
		}
		else if (x >= 15 && x < 20)
		{
			if (!isExcellent)
			{
				_mySonic->scoreMul = 2.5;
				_evaluate->setColor(Color3B(255, 128, 0));
				//_evaluate->setString("Excellent!");
				isExcellent = true;
			}
			else _evaluate->setString("");
		}
		else if (x >= 20)
		{
			if (!isPerfect)
			{
				_mySonic->scoreMul = 3.0;
				_evaluate->setColor(Color3B(255, 0, 0));
				//_evaluate->setString("Perfect!");
				isPerfect = true;
			}
			else _evaluate->setString("");
		}
		_evaluate->enableOutline(Color4B::BLACK, 3);

		_evaluate->runAction(
			Sequence::create(
				FadeIn::create(0.1),
				MoveBy::create(0.5, Vec2(0, 15)),
				DelayTime::create(1),
				FadeOut::create(0.1), nullptr));
	}
}

void RingComboScore::update(float dt)
{
	//Label count 

	_countRing->setString("X  " + std::to_string(_mySonic->ringCollected));

	if (_prev_score != _mySonic->score)
	{
		_delta_score = _mySonic->score - _prev_score;
	}

	int combo = _mySonic->countCombo;
	if (_pre_combo != combo)
	{
		if (combo == 0)
		{
			ResetCombo();
			flame->setVisible(false);
		}
		else
		{
			UpdateCombo();

			if (combo <= 5) flame->setVisible(false);
			else flame->setVisible(true);
			if (combo > 5 && combo <= 10 && _pre_combo <= 5)
			{
				flame->stopAllActions();
				flame->runAction(RepeatForever::create(flame_blue_Ani->get()));
			}
			else if (combo > 10 && combo <= 15 && _pre_combo <= 10)
			{
				flame->stopAllActions();
				flame->runAction(RepeatForever::create(flame_Ani->get()));
			}
			else if (combo > 15 && _pre_combo <= 20 && _pre_combo <= 15)
			{
				flame->stopAllActions();
				flame_Ani = new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(flame_FL, 0.04f)));
				//	flame_Ani->get()->getAnimation()->setsetDelayPerUnit(0.02f);
				flame->runAction(RepeatForever::create(flame_Ani->get()));
			}
			else if (combo > 20 && _pre_combo <= 20)
			{
				flame->stopAllActions();
				flame_Ani = new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(flame_FL, 0.02f)));
				flame->runAction(RepeatForever::create(flame_Ani->get()));
			}

		}
		SetColor();
	}
	_pre_combo = _mySonic->countCombo;
	_prev_score = _mySonic->score;
}