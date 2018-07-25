#include "MonkeyMonster.h"




MonkeyMonster::MonkeyMonster(Sonic * sonic, Vec2 pos)
{
	Vector<SpriteFrame*> runFL = loadAnim("Monster/monkey.xml", "run");
	Vector<SpriteFrame*> fightFL = loadAnim("Monster/monkey.xml", "fight");

	_runAni = new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(runFL, 0.07f)));
	_fightAni = new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(fightFL, 0.08f)));


	Monster::Init(sonic);
	_multiButton->_action = SonicState::RUN_FAST;
	this->setPosition(pos);
	this->setScale(0.7);
	this->getPhysicsBody()->setGravityEnable(false);

}

MonkeyMonster::~MonkeyMonster()
{
}

void MonkeyMonster::update(float dt)
{
	if (isDelete) return;

	_multiButton->setPosition(this->getPosition()+Vec2(-70,120));
	_time_action++;
	switch (_currentState)
	{
	case RUN:
		if (this->getPositionX() - _mSonic->getPositionX() <500 && !isActive)
		{
			isActive = true;
			SetStateByTag(FIGHT);
		}
		if (_time_action == 100)
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
		if (CheckLastFrame())
		{
			SetStateByTag(RUN);
		}
		break;
	default:
		break;
	}
	if (this->getPositionX() - _mSonic->getPositionX() < 100 && _multiButton->isTrue)
	{
		isDelete = true;
		_mSonic->SetStateByTag(SonicState::COUNTER);
	}
	
}

void MonkeyMonster::SetStateByTag(MONSTERSTATE state)
{
	this->stopAllActions();
	_currentState = state;
	_time_action = 0;
	switch (state)
	{
	
	case RUN:
		_currentAnimate = _runAni;
		_currentAction = RepeatForever::create(_currentAnimate->get()->clone());
		if (this->getPosition().x - _mSonic->getPosition().x < 1000) //Fix when move scene, Monster move wrong position
		{
			if (!_isLeft) this->getPhysicsBody()->setVelocity(Vec2(0,50));
			else  this->getPhysicsBody()->setVelocity(Vec2(0, -50));
		}
		else	this->getPhysicsBody()->setVelocity(Vec2(0, 0));

		break;
	case DIE:
		_currentAnimate = _dieAni;
		_currentAction = _currentAnimate->get()->clone();
		this->getPhysicsBody()->setContactTestBitmask(0);
		break;
	case FIGHT:
	

		{
		this->getPhysicsBody()->setVelocity(Vec2(0, 0)); 
		auto coconut = Sprite::create("Monster/Coconut.png");
		auto physic_body = PhysicsBody::createCircle(coconut->getContentSize().width / 2);
		physic_body->setRotationEnable(true);
		physic_body->setMass(210);

		physic_body->setCategoryBitmask(16);    // 0010
		physic_body->setCollisionBitmask(0);   // 0001
		physic_body->setContactTestBitmask(1);

	/*	physic_body->setCategoryBitmask(0);
		physic_body->setCollisionBitmask(0);
		physic_body->setContactTestBitmask(16);*/
		coconut->setTag(Define::COCONUT);
		
		coconut->setPhysicsBody(physic_body);
		coconut->setPosition(this->getPosition()+Vec2(0,50));
		coconut->getPhysicsBody()->setAngularVelocity(10);
		coconut->getPhysicsBody()->applyImpulse(Vec2(-23000, 50000));

		this->getParent()->addChild(coconut);


		_currentAnimate = _fightAni;
		_currentAction = _currentAnimate->get(); }
		break;
	default:
		break;
	}
	this->runAction(_currentAction);
}
