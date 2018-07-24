#include "SharkMonster.h"



SharkMonster::SharkMonster(Sonic *sonic, Vec2 pos)
{
	Vector<SpriteFrame*> runFL = loadAnim("Monster/shark.xml", "run");
	Vector<SpriteFrame*> fightFL = loadAnim("Monster/shark.xml", "bite");

	_runAni = new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(runFL, 0.07f)));
	_fightAni = new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(fightFL, 0.08f)));

	
	_water_splash= new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(Define::loadAnim("Particle/water_splash.xml","1"), 0.05f)));

	this->initWithSpriteFrame(runFL.at(0));
	auto verti = PhysicsBody::createBox(this->getContentSize(), PhysicsMaterial(0.1f, 0.6, 0.0f));

	verti->setCategoryBitmask(16);    // 0010
	verti->setCollisionBitmask(0);   // 0001
	verti->setContactTestBitmask(1);
	

	verti->setGravityEnable(false);


	this->setPhysicsBody(verti);
	this->setTag(LANDMONSTER);

	_mSonic = sonic;

	_tapButton = new TapButton(pos, _mSonic, (Layer*)_mSonic->getParent());
	_tapButton->SetCanActive(true);
	_tapButton->_action = SonicState::RUN_FAST;

	this->setPosition(pos);
	this->setAnchorPoint(Vec2(0.5f, 0));
	this->SetStateByTag(RUN);
	this->scheduleUpdate();



	
}

void SharkMonster::update(float dt)
{
	//When fall, flip down
	if (this->getPhysicsBody()->getVelocity().y < -10 && !_flipped)
	{

		_flipped = true;
		this->setFlippedY(true);

	}

	//When fall to water, run water splash animation
	if (water != nullptr)
	{
		if (this->getPositionY() < water->getPositionY())
		{
			water->setOpacity(255);
			water->runAction(Sequence::create(_water_splash->get()->clone(), RemoveSelf::create(), nullptr));
			water = nullptr;
			isDelete = true;
			this->setVisible(false);
			this->runAction(Sequence::create(DelayTime::create(1.5), RemoveSelf::create(), nullptr));
		}
	}


	if (isDelete) return;

	//Update position tapbutton
	_tapButton->setPosition(this->getPosition() + Vec2(0, 150));
	

	

	_time_action++;
	this->setFlipX(_isLeft);
	switch (_currentState)
	{
	case RUN:
		if (_time_action ==25)
		{
			_isLeft = !_isLeft;
			SetStateByTag(RUN);
		}
		break;
	case DIE:
		if (_time_action == 100)
		{
			MyParticle::CreateLandSmoke(this->getPosition(), (Layer*) this->getParent());
			this->runAction(RemoveSelf::create());
			return;
		}
		break;
	case FIGHT:
		break;
	default:
		break;
	}

	if (!_isButtonActive)
	{
		if (_tapButton->isTrue) 
		{
			if (_tapButton->score == PERFECT)
			{
				_mSonic->SetStateByTag(SonicState::RUNSKIP);
				_tapButton->_action = SonicState::RUN_FAST;
				_isActiveEarly = false;
			}
			else
			{
				_isActiveEarly = true;
			}
			_isButtonActive = true;
		}
	}
	else
	{
		if (!_isActiveEarly)
		{
			if (_mSonic->getPositionX() - this->getPositionX() >40 )
			{
				this->SetStateByTag(FIGHT);
				isDelete = true;
			}
		}
		else
		{
			if (this->getPositionX() - _mSonic->getPositionX() < 100)
			{
				_mSonic->SetStateByTag(SonicState::STOP);
				this->SetStateByTag(FIGHT);
				isDelete = true;
			}
		}
	}

	//If press wrong or no press
	if (_tapButton->isDelete && this->getPositionX() - _mSonic->getPositionX()<20 && _tapButton->score!=PERFECT)
	{
		this->SetStateByTag(FIGHT);
		isDelete = true;
	}
	
}

void SharkMonster::SetStateByTag(MONSTERSTATE state)
{
	this->stopAllActions();
	_currentState = state;
	_time_action = 0;
	switch (state)
	{
	case IDLE:
		_currentAnimate = _idleAni;
		_currentAction = RepeatForever::create(_currentAnimate->get()->clone());
		this->getPhysicsBody()->setVelocity(Vec2(0, 0));
		break;
	case RUN:
		_currentAnimate = _runAni;
		_currentAction = RepeatForever::create(_currentAnimate->get()->clone());
		if (this->getPosition().x - _mSonic->getPosition().x < 1000) //Fix when move scene, Monster move wrong position
		{
			if (!_isLeft) this->getPhysicsBody()->setVelocity(Vec2(-100, 0));
			else  this->getPhysicsBody()->setVelocity(Vec2(100, 0));
		}
		else	this->getPhysicsBody()->setVelocity(Vec2(0, 0));

		break;
	case DIE:
		_currentAnimate = _dieAni;
		_currentAction = _currentAnimate->get()->clone();
		this->getPhysicsBody()->setContactTestBitmask(0);
		break;
	case FIGHT:
		water = Sprite::create();
		water->setAnchorPoint(Vec2(0.5, 0));
		water->setPosition(this->getPosition());
		this->getParent()->addChild(water);
		water->runAction(Sequence::create(_water_splash->get()->clone(), FadeTo::create(0,0), nullptr));
		
		//
		_currentAnimate = _fightAni;
		_currentAction = RepeatForever::create(_currentAnimate->get()->clone());
		
		//
		this->getPhysicsBody()->setGravityEnable(true);
		this->getPhysicsBody()->setPositionOffset(Vec2(10, 0));
		this->getPhysicsBody()->setVelocity(Vec2(0, 0));
		this->getPhysicsBody()->applyForce(Vec2(0,13000000));
		break;
	default:
		break;
	}
	this->runAction(_currentAction);
}


SharkMonster::~SharkMonster()
{
}
