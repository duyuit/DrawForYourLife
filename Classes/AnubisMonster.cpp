#include "AnubisMonster.h"
#include "Pyramid_Anubis.h"

AnubisMonster::AnubisMonster(Sonic * sonic, Vec2 pos)
{
	Vector<SpriteFrame*> dieFL = loadAnim("Monster/Desert/AnubisMonster.xml", "die");
	Vector<SpriteFrame*> die2FL = loadAnim("Monster/Desert/AnubisMonster.xml", "die2");
	Vector<SpriteFrame*> die3FL = loadAnim("Monster/Desert/AnubisMonster.xml", "die3");
	Vector<SpriteFrame*> idleFL = loadAnim("Monster/Desert/AnubisMonster.xml", "idle");
	Vector<SpriteFrame*> fightFL = loadAnim("Monster/Desert/AnubisMonster.xml", "fight");

	_dieAni = new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(dieFL, 0.2f)));
	_die2Ani = new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(die2FL, 0.2f)));
	_die3Ani = new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(die3FL, 0.2f)));
	_idleAni = new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(idleFL, 0.1f)));
	_fightAni = new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(fightFL, 0.07f)));

	this->initWithSpriteFrame(_idleAni->get()->getAnimation()->getFrames().at(0)->getSpriteFrame());
	auto verti = PhysicsBody::createBox(this->getContentSize(), PhysicsMaterial(0.1f, 0.6, 0.0f));

	verti->setCategoryBitmask(16);    // 0010
	verti->setCollisionBitmask(2);   // 0001
	verti->setContactTestBitmask(1);

	verti->setRotationEnable(false);
	verti->setDynamic(true);

	this->setPhysicsBody(verti);
	SetStateByTag(IDLE);
	this->setTag(LANDMONSTER);

	_mSonic = sonic;

	this->setAnchorPoint(Vec2(0.5f, 0));
	this->setPosition(pos);
	this->scheduleUpdate();

	_multiButton = new MultipleButton(pos, sonic, (Layer*)sonic->getParent(), 3, 2);
	_multiButton->_action = SonicState::RUN_FAST;
}

void AnubisMonster::update(float dt)
{
	_multiButton->setPosition(this->getPosition() + Vec2(-70, 120));
	if (isDelete) return;

	if (this->getPositionX() - _mSonic->getPositionX() < 150 && _multiButton->isTrue)
	{
		isDelete = true;
		_mSonic->SetStateByTag(SonicState::COUNTER);
	}

	_time_action++;
	switch (_currentState)
	{
	case DIE:
		break;
	case IDLE:
		if (this->getPositionX() - _mSonic->getPositionX() < 500 && !isActive)
		{		
			SetStateByTag(FIGHT);
			isActive = true;
		}
		break;
	case FIGHT:
		if (_time_action == 40)
		{
			auto pyramid = new Pyramid_Anubis();

			pyramid->setPosition(this->getPosition() + Vec2(-40, 70));
			pyramid->getPhysicsBody()->applyImpulse(Vec2(-20000, -20000));
			pyramid->_pyramid = this;
			this->getParent()->addChild(pyramid);	
		}
		if (_time_action == 60)
			SetStateByTag(IDLE);
		break;
	default:
		break;
	}
}

void AnubisMonster::SetStateByTag(MONSTERSTATE state)
{
	this->stopAllActions();
	_currentState = state;
	_time_action = 0;

	switch (state)
	{
	case FIGHT:
		_currentAnimate = _fightAni;
		_currentAction = _currentAnimate->get()->clone();
		break;

	case DIE:
	{
		int t = RandomHelper::random_int(1, 3);
		if (t == 1)
			_currentAnimate = _dieAni;
		else if (t == 2)
			_currentAnimate = _die2Ani;
		else _currentAnimate = _die3Ani;

		_currentAction = _currentAnimate->get()->clone();

		//ScaleTo* delay = ScaleTo::create(100 / 60.0f, 1.0f);
		DelayTime* delay = DelayTime::create(1.0f);
		CallFunc* dieState = CallFunc::create([&] {
			MyParticle::CreateLandSmoke(this->getPosition(), (Layer*) this->getParent());
			this->runAction(RemoveSelf::create());
			isDelete = true;
		});

		this->runAction(Sequence::create(delay, dieState, nullptr));

		this->getPhysicsBody()->setContactTestBitmask(0);
		this->getPhysicsBody()->applyImpulse(Vec2(180000, 180000));
	}
		break;
	
	case IDLE:
		_currentAnimate = _idleAni;
		_currentAction = RepeatForever::create(_currentAnimate->get()->clone());
		this->getPhysicsBody()->setVelocity(Vec2(0, 0));
		break;
	default:
		break;
	}
	this->runAction(_currentAction);
}

AnubisMonster::~AnubisMonster()
{
}
