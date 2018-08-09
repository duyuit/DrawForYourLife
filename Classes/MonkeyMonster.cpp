#include "MonkeyMonster.h"

#include "Coconut_Monkey.h"


MonkeyMonster::MonkeyMonster(Sonic * sonic, Vec2 pos)
{
	Vector<SpriteFrame*> runFL = loadAnim("Monster/monkey.xml", "run");
	Vector<SpriteFrame*> fightFL = loadAnim("Monster/monkey.xml", "fight");

	_runAni = new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(runFL, 0.07f)));
	_fightAni = new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(fightFL, 0.08f)));


	Monster::Init(sonic);
	_multiButton = new MultipleButton(pos, sonic, (Layer*)sonic->getParent(), 3, 2);
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

	if (this->getPositionX() - _mSonic->getPositionX() < 170 && _multiButton->isTrue)
	{
		isDelete = true;
		_mSonic->SetStateByTag(SonicState::COUNTER);
	}

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
		if (_time_action == 30)
		{
			_isLeft = !_isLeft;
			SetStateByTag(RUN);
		}
		break;
	case DIE:
	
			MyParticle::CreateLandSmoke(this->getPosition(), (Layer*) this->getParent());
		
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
	
	case FIGHT:
	

		{
		this->getPhysicsBody()->setVelocity(Vec2(0, 0)); 
		auto coconut =new  Coconut_Monkey();
	
		
		
		coconut->setPosition(this->getPosition()+Vec2(0,50));
		coconut->getPhysicsBody()->setAngularVelocity(10);
		coconut->getPhysicsBody()->applyImpulse(Vec2(-23000, 50000));
		coconut->khi = this;

		this->getParent()->addChild(coconut);


		_currentAnimate = _fightAni;
		_currentAction = _currentAnimate->get(); }
		break;
	case DIE:
		MyParticle::CreateLandSmoke(this->getPosition(), (Layer*) this->getParent());
		this->runAction( RemoveSelf::create());
		isDelete = true;
		this->getPhysicsBody()->setContactTestBitmask(0);
		return;
		break;
	default:
		break;
	}
	this->runAction(_currentAction);
}
