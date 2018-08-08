#include "LizardMonster.h"

LizardMonster::LizardMonster(Sonic * sonic)
{
	Vector<SpriteFrame*> runFL = loadAnim("Monster/Desert/LizardMonster.xml", "run");
	Vector<SpriteFrame*> dieFL = loadAnim("Monster/Desert/LizardMonster.xml", "die");
	Vector<SpriteFrame*> idleFL = loadAnim("Monster/Desert/LizardMonster.xml", "idle");
	Vector<SpriteFrame*> fightFL = loadAnim("Monster/Desert/LizardMonster.xml", "fight");

	_runAni = new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(runFL, 0.07f)));
	_dieAni = new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(dieFL, 0.2f)));
	_idleAni = new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(idleFL, 0.1f)));
	_fightAni = new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(fightFL, 0.05f)));

	Monster::Init(sonic);
	_multiButton = new MultipleButton(Vec2(0, 0), _mSonic, (Layer*)_mSonic->getParent(), 2, 2);
}

void LizardMonster::SetStateByTag(MONSTERSTATE state)
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
			if (_isLeft) this->getPhysicsBody()->setVelocity(Vec2(-30, 0));
			else  this->getPhysicsBody()->setVelocity(Vec2(30, 0));
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
		break;
	default:
		break;
	}
	this->runAction(_currentAction);
}

LizardMonster::~LizardMonster()
{
}
