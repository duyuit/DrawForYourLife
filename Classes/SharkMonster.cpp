#include "SharkMonster.h"



SharkMonster::SharkMonster(Sonic *sonic)
{
	Vector<SpriteFrame*> runFL = loadAnim("Monster/shark.xml", "run");
	//	Vector<SpriteFrame*> dieFL = loadAnim("Monster/frog.xml", "die");
	//Vector<SpriteFrame*> idleFL = loadAnim("Monster/frog.xml", "idle");
	Vector<SpriteFrame*> fightFL = loadAnim("Monster/shark.xml", "bite");

	_runAni = new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(runFL, 0.07f)));
	//_dieAni = new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(dieFL, 0.2f)));
	//_idleAni = new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(idleFL, 0.1f)));
	_fightAni = new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(fightFL, 0.05f)));

	Monster::Init(sonic);
	this->setAnchorPoint(Vec2(0.5, 0));
	this->getPhysicsBody()->getShape(0)->setRestitution(0);
	//_isLeft = true;
	//this->setFlippedX(_isLeft);
	//this->setScale(0.8);
	this->SetStateByTag(RUN);
}

void SharkMonster::update(float dt)
{
	if (this->getPhysicsBody()->getVelocity().y < -10 && !_flipped)
	{
		_flipped = true;
		this->setFlippedY(true);
	}
	_multiButton->setPosition(this->getPosition() + Vec2(0, 150));
	_time_action++;
	this->setFlipX(_isLeft);
	switch (_currentState)
	{
	case RUN:
		if (_time_action ==100)
		{
			_isLeft = !_isLeft;
			SetStateByTag(FIGHT);
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
		if (this->getPosition().x - _sonic->getPosition().x < 1500) //Fix when move scene, Monster move wrong position
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
		_currentAnimate = _fightAni;
		_currentAction = RepeatForever::create(_currentAnimate->get()->clone());
		this->getPhysicsBody()->setVelocity(Vec2(0, 0));
		this->getPhysicsBody()->applyForce(Vec2(0,50000000));
		break;
	default:
		break;
	}
	this->runAction(_currentAction);
}


SharkMonster::~SharkMonster()
{
}
