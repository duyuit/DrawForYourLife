#include "BossLv1.h"


BossLv1::BossLv1(Vec2 pos , Sonic* sonic, Layer* layer)
{
	drill = new BossDrill();
	drill->parent = this;

	plane = new BossPlane();

	drill->setPosition(pos);
	_mSonic = sonic;

	auto active_car = CallFunc::create([this]()
	{
		drill->ActiveDrill();
		plane->ActiveWing(false);
	});
	plane->setPosition(pos+Vec2(500,500));


	
	plane->runAction(Sequence::create(
		MoveTo::create(2, pos+Vec2(110,50 + 300)),
		DelayTime::create(0.4),
		MoveBy::create(2,Vec2(0,-300)),
		DelayTime::create(0.3),
		active_car,
		nullptr));
	this->scheduleUpdate();
	layer->addChild(drill,10);
	layer->addChild(plane,9);
	this->setPosition(pos);

}


BossLv1::~BossLv1()
{
}

void BossLv1::SetState(STATE state)
{
	switch (state)
	{
	case BossLv1::IDLE:
		drill->chain1->getPhysicsBody()->setCollisionBitmask(0);
		break;
	case BossLv1::RUN:
	{
		drill->chain1->setVisible(false);
		drill->chain2->setVisible(false);
		drill->chain3->setVisible(false);

		drill->chain1->getPhysicsBody()->setCollisionBitmask(0);

		currentButton = new TapButton(this->getPosition() + Vec2(0, 300), _mSonic, (Layer*)this->getParent());
		currentButton->time = 0.8;
		currentButton->SetCanActive(true);
		currentButton->_action = SonicState::ROLL_IN_SKY;
		
	
			
		
			auto flip = CallFunc::create([this]() {
				drill->Flip(true);
				plane->Flip(true);
			});
		
			drill->runAction(Sequence::create(
				MoveBy::create(5, Vec2(-1500, 0)),
				flip,
				NULL));
			plane->runAction(Sequence::create(
				MoveBy::create(5, Vec2(-1500, 0)),
				NULL));
	}
		break;
	case BossLv1::RUNBACK:
	{
		currentButton = new TapButton(this->getPosition() + Vec2(0, 300), _mSonic, (Layer*)this->getParent());
		currentButton->time = 0.8;
		currentButton->SetCanActive(true);
		currentButton->_action = SonicState::ROLL_IN_SKY;
		auto flip2 = CallFunc::create([this]() {
			drill->Flip(true);
			plane->Flip(true);
		});

		auto flip = CallFunc::create([this]() {
			drill->Flip(false);
			plane->Flip(false);
		});

		drill->runAction(Sequence::create(
			MoveBy::create(5, Vec2(1800, 0)),
			flip,
			MoveBy::create(1, Vec2(-300, 0)),
			NULL));
		plane->runAction(Sequence::create(
			MoveBy::create(5, Vec2(1800, 0)),
			MoveBy::create(1, Vec2(-300, 0)),
			NULL));
	}
		break;

	case BossLv1::FIGHT:
		{	

		drill->chain1->setVisible(true);
		drill->chain2->setVisible(true);
		drill->chain3->setVisible(true);

		drill->chain1->getPhysicsBody()->setCollisionBitmask(1);
		currentButton = new TapButton(this->getPosition()+Vec2(0,300), _mSonic, (Layer*)this->getParent());
		currentButton->time = 0.8;
		currentButton->SetCanActive(true);
		currentButton->_action = SonicState::ROLL_IN_SKY;
		drill->FireDrill(); 
		}
		break;	
	case BossLv1::GETBACKDRILL:
		{
		delete currentButton;
		currentButton = new TapButton(this->getPosition() + Vec2(0, 300), _mSonic, (Layer*)this->getParent());
		currentButton->time = 0.6;
		currentButton->SetCanActive(true);
		currentButton->_action = SonicState::ROLL_IN_SKY;
		}
		break;
	default:
		break;
	}
	currentState = state;
}

void BossLv1::update(float dt)
{
	if (currentButton != nullptr)
	{
		//if(currentState==FIGHT || currentState == GETBACKDRILL)
		currentButton->setPosition(_mSonic->getPosition() + Vec2(350, 200));

		float currentDrillPosition = drill->getPositionX() + drill->drill->getPositionX();

		if (currentState == FIGHT)
		{
			if (currentDrillPosition - _mSonic->getPositionX() < 50
				&& currentButton->isTrue
				&&_mSonic->mCurrentState->GetState() != SonicState::ROLL_IN_SKY)
			{

				_mSonic->SetStateByTag(SonicState::ROLL_IN_SKY);
				_mSonic->isLeft = true;
				currentButton = nullptr;


			}
		}
		else if (currentState == GETBACKDRILL)
		{
			if (_mSonic->getPositionX() - currentDrillPosition < 600
				&& currentButton->isTrue
				&& _mSonic->mCurrentState->GetState() != SonicState::ROLL_IN_SKY)
			{

				_mSonic->SetStateByTag(SonicState::ROLL_IN_SKY);
				_mSonic->isLeft = false;
				currentButton = nullptr;

			}
		}
		else if (currentState == RUN)
		{
				if (currentDrillPosition - _mSonic->getPositionX() < 300
					&& currentButton->isTrue
					&& _mSonic->mCurrentState->GetState() != SonicState::ROLL_IN_SKY)
				{
						_mSonic->SetStateByTag(SonicState::ROLL_IN_SKY);
						_mSonic->getPhysicsBody()->applyImpulse(Vec2(0, 100000));
						_mSonic->isLeft = true;
						currentButton = nullptr;
				}

		}
		else if (currentState == RUNBACK)
		{
			if (_mSonic->getPositionX() - currentDrillPosition < 500
				&& currentButton->isTrue
				&& _mSonic->mCurrentState->GetState() != SonicState::ROLL_IN_SKY)
			{
				_mSonic->SetStateByTag(SonicState::ROLL_IN_SKY);
				_mSonic->getPhysicsBody()->applyImpulse(Vec2(0, 100000));
				_mSonic->isLeft = true;
				currentButton = nullptr;
			}

		}
	}
	if (drill->getPositionX() < _mSonic->getPositionX())
		_mSonic->isLeft = true;
	else _mSonic->isLeft = false;
	count_to_change_state++;
	switch (currentState)
	{
	case BossLv1::RUNBACK:
		if (count_to_change_state == 60 * 6)
		{
			count_to_change_state = 0;
			SetState(FIGHT);
		}
	case BossLv1::IDLE:
		if (count_to_change_state == 60 *6)
		{
			count_to_change_state = 0;
			SetState(FIGHT);
		}
		break;
	case BossLv1::RUN:
		if (count_to_change_state == 60 *5)
		{
			count_to_change_state = 0;
			SetState(RUNBACK);
		}
		break;
	case BossLv1::FIGHT:
	
		break;
	case BossLv1::GETBACKDRILL:
		if (count_to_change_state == 60 *5)
		{
			count_to_change_state = 0;
			SetState(RUN);
		}
		break;
	default:
		break;
	}

	//if (count_to_change_state == 60*6)
	//{
	////	count_to_change_state = 0;
	//	SetState(RUN);
	//}
}

void BossLv1::Merge()
{
}

void BossLv1::Flip()
{
	//drill->Flip();

}
