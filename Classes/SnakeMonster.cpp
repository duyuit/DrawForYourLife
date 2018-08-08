#include "SnakeMonster.h"

SnakeMonster::SnakeMonster(Sonic * sonic)
{
	Vector<SpriteFrame*> runFL = loadAnim("Monster/Desert/SnakeMonster.xml", "run");
	Vector<SpriteFrame*> dieFL = loadAnim("Monster/Desert/SnakeMonster.xml", "die");
	Vector<SpriteFrame*> idleFL = loadAnim("Monster/Desert/SnakeMonster.xml", "idle");
	Vector<SpriteFrame*> fightFL = loadAnim("Monster/Desert/SnakeMonster.xml", "fight");

	_runAni = new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(runFL, 0.07f)));
	_dieAni = new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(dieFL, 0.2f)));
	_idleAni = new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(idleFL, 0.1f)));
	_fightAni = new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(fightFL, 0.12f)));

	Monster::Init(sonic);
	_multiButton = new MultipleButton(Vec2(0, 0), _mSonic, (Layer*)_mSonic->getParent(), 3, 2);
}

void SnakeMonster::update(float dt)
{
	_multiButton->setPosition(this->getPosition() + Vec2(0, 150));
	_time_action++;
	this->setFlipX(_isLeft);
	switch (_currentState)
	{
	case IDLE:
		if (_time_action == 30)
		{
			SetStateByTag(RUN);
			_isLeft = !_isLeft;
		}
		break;
	case RUN:
		if (_time_action == 120)
		{
			SetStateByTag(IDLE);
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
			SetStateByTag(IDLE);
		}
		break;
	default:
		break;
	}

	if (isAttack)
	{
		if (this->getPosition().x - _mSonic->getPosition().x < 200 && !_isLeft)
		{
			SetStateByTag(FIGHT);
			isAttack = false;
		}	
	}
}

void SnakeMonster::SetStateByTag(MONSTERSTATE state)
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
		if (this->getPosition().x - _mSonic->getPosition().x < 1500) //Fix when move scene, Monster move wrong position
		{
			if (_isLeft) this->getPhysicsBody()->setVelocity(Vec2(-50, 0));
			else  this->getPhysicsBody()->setVelocity(Vec2(50, 0));
		}
		else
			this->getPhysicsBody()->setVelocity(Vec2(0, 0));

		break;
	case DIE:
		_currentAnimate = _dieAni;
		_currentAction = _currentAnimate->get()->clone();
		this->getPhysicsBody()->setContactTestBitmask(0);
		break;
	case FIGHT:
		_currentAnimate = _fightAni;
		_currentAction = _currentAnimate->get()->clone();	
		break;
	default:
		break;
	}
	this->runAction(_currentAction);
}

SnakeMonster::~SnakeMonster()
{
}