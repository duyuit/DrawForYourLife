#include "SandRatMonster.h"
SandRatMonster::SandRatMonster(Sonic * sonic, Vec2 pos)
{
	Vector<SpriteFrame*> runFL = loadAnim("Monster/Desert/SandRatMonster.xml", "run");
	Vector<SpriteFrame*> dieFL = loadAnim("Monster/Desert/SandRatMonster.xml", "die");
	Vector<SpriteFrame*> idleFL = loadAnim("Monster/Desert/SandRatMonster.xml", "idle");
	Vector<SpriteFrame*> fightFL = loadAnim("Monster/Desert/SandRatMonster.xml", "fight");

	_runAni = new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(runFL, 0.07f)));
	_dieAni = new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(dieFL, 0.07f)));
	_idleAni = new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(idleFL, 0.15f)));
	_fightAni = new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(fightFL, 0.05f)));

	//Init
	this->initWithSpriteFrame(_idleAni->get()->getAnimation()->getFrames().at(0)->getSpriteFrame());
	auto verti = PhysicsBody::createBox(this->getContentSize(), PhysicsMaterial(0.1f, 0.6, 0.0f));

	verti->setCategoryBitmask(16);    // 0010
	verti->setCollisionBitmask(2);   // 0001
	verti->setContactTestBitmask(1);

	verti->setRotationEnable(false);
	verti->setDynamic(true);


	this->setPhysicsBody(verti);
	this->setTag(SANDRAT);

	_mSonic = sonic;

	this->setPosition(pos);
	this->setAnchorPoint(Vec2(0.5f, 0));
	SetStateByTag(RUN);
	this->scheduleUpdate();

	_tapButton = new TapButton(pos, _mSonic, (Layer*)_mSonic->getParent());
	_tapButton->SetCanActive(true);
}

void SandRatMonster::HandleCollision(Sprite * sprite)
{
	if (sprite->getTag() == Player)
	{
		Sonic* sonic = (Sonic*)sprite;
		if ((sonic->mCurrentState->GetState() == SonicState::FALL 
			|| sonic->mCurrentState->GetState() == SonicState::JUMP) && _currentState != DIE)
		{
			this->SetStateByTag(DIE);
		}
	}
}

void SandRatMonster::update(float dt)
{
	_tapButton->setPosition(this->getPosition() - Vec2(350, -200));

	_time_action++;
	switch (_currentState)
	{
	case IDLE:
		if (_time_action == 60)
		{
			SetStateByTag(RUN);
		}
		break;
	case RUN:
		if (_time_action == 60)
		{
			SetStateByTag(IDLE);
		}
		break;
	case DIE:
		if (_time_action == 60)
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

void SandRatMonster::SetStateByTag(MONSTERSTATE state)
{
	this->stopAllActions();
	_currentState = state;
	_time_action = 0;

	switch (state)
	{
	case IDLE:
		_currentAnimate = _idleAni;
		_currentAction = _currentAnimate->get()->clone();
		this->getPhysicsBody()->setVelocity(Vec2(0, 0));
		break;
	case RUN:
		_currentAnimate = _runAni;
		_currentAction = _currentAnimate->get()->clone(); 
		this->getPhysicsBody()->setVelocity(Vec2(0, 0));
		break;
	case DIE:
		_currentAnimate = _dieAni;
		_currentAction = _currentAnimate->get()->clone();
		this->getPhysicsBody()->setContactTestBitmask(0);
	case FIGHT:
		_currentAnimate = _fightAni;
		break;
	default:
		break;
	}
	this->runAction(_currentAction);
}

SandRatMonster::~SandRatMonster()
{
}
