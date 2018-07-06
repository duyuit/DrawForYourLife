#include "Monster.h"
#include "GameDefine.h"
#include "Sonic.h"
#include "SmallRing.h"
using namespace Define;

Monster::Monster()
{
	Vector<SpriteFrame*> runFL = loadAnim("Monster/frog.xml", "run");
	Vector<SpriteFrame*> dieFL = loadAnim("Monster/frog.xml", "die");
	Vector<SpriteFrame*> idleFL = loadAnim("Monster/frog.xml", "idle");
	Vector<SpriteFrame*> fightFL = loadAnim("Monster/frog.xml", "fight");

	_runAni=  new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(runFL, 0.07f)));
	_dieAni= new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(dieFL, 0.2f)));
	_idleAni= new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(idleFL, 0.1f)));
	_fightAni= new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(fightFL, 0.05f)));

	//this->Init(sonic);

	
}

void Monster::Init(Sonic * sonic)
{
	this->initWithSpriteFrame(_idleAni->get()->getAnimation()->getFrames().at(0)->getSpriteFrame());
	auto verti = PhysicsBody::createBox(this->getContentSize(), PhysicsMaterial(0.1f,0.6,0.0f));

	verti->setCategoryBitmask(16);    // 0010
	verti->setCollisionBitmask(2);   // 0001
	verti->setContactTestBitmask(1);

	verti->setRotationEnable(false);
	verti->setDynamic(true);
	this->setPhysicsBody(verti);
	this->setTag(LANDMONSTER);

	_sonic = sonic;
	_tapButton = new TapButton(RandomHelper::random_int(1, 4), Vec2(0, 0), _sonic, (Layer*)_sonic->getParent());
	_tapButton->isFirst = true;
	_tapButton->_time_circle_shrink = 0.7;
	_tapButton->_action = SonicState::ROLL;

	this->setAnchorPoint(Vec2(0.5f, 0));
	SetStateByTag(IDLE);
	this->scheduleUpdate();
}


void Monster::HandleCollision(Sprite * sprite)
{
	if (sprite->getTag() == Player)
	{
		Sonic* sonic = (Sonic*)sprite;
		if (sonic->mCurrentState->GetState() == SonicState::ROLL && _currentState != DIE)
		{
			this->getPhysicsBody()->applyImpulse(Vec2(200000, 200000));
			this->SetStateByTag(DIE);
		}
	}
}

void Monster::update(float dt)
{
	_tapButton->setPosition(this->getPosition()+Vec2(0,150));

	_time_action++;
	this->setFlipX(_isLeft);
	switch (_currentState)
	{
	case IDLE:
		if (_time_action == 60)
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
		if (_time_action ==100)
		{
			MyParticle::CreateLandSmoke(this->getPosition(),(Layer*) this->getParent());
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

void Monster::SetStateByTag(MONSTERSTATE state)
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
		if (_isLeft) this->getPhysicsBody()->setVelocity(Vec2(-100, 0));
		else  this->getPhysicsBody()->setVelocity(Vec2(100, 0));
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

Monster::~Monster()
{
}
