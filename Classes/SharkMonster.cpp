#include "SharkMonster.h"



SharkMonster::SharkMonster(Sonic *sonic)
{
	Vector<SpriteFrame*> runFL = loadAnim("Monster/shark.xml", "run");
	Vector<SpriteFrame*> fightFL = loadAnim("Monster/shark.xml", "bite");

	_runAni = new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(runFL, 0.07f)));
	_fightAni = new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(fightFL, 0.05f)));

	
	_water_splash= new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(Define::loadAnim("Particle/water_splash.xml","1"), 0.05f)));
//	Monster::Init(sonic);

	this->initWithSpriteFrame(runFL.at(0));
	auto verti = PhysicsBody::createBox(this->getContentSize(), PhysicsMaterial(0.1f, 0.6, 0.0f));

	verti->setCategoryBitmask(16);    // 0010
	verti->setCollisionBitmask(2);   // 0001
	verti->setContactTestBitmask(1);

	verti->setRotationEnable(false);
	verti->setDynamic(true);


	this->setPhysicsBody(verti);
	this->setTag(LANDMONSTER);

	_mSonic = sonic;
	/*_tapButton = new TapButton(Vec2(0, 0), _mSonic, (Layer*)_mSonic->getParent());
	_tapButton->isFirst = true;
	_tapButton->_time_circle_shrink = 0.7;
	_tapButton->_action = SonicState::ROLL;*/

	_multiButton = new MultipleButton(Vec2(0, 0), _mSonic, (Layer*)_mSonic->getParent(), 3, 2);

	//this->addChild(_multiButton,10);

	this->setAnchorPoint(Vec2(0.5f, 0));
	SetStateByTag(IDLE);
	this->scheduleUpdate();


	this->getPhysicsBody()->getShape(0)->setRestitution(0);

	//this->getPhysicsBody()->setCollisionBitmask(0);
	this->SetStateByTag(RUN);
}

void SharkMonster::update(float dt)
{
	if (isDelete) return;
	if (this->getPhysicsBody()->getVelocity().y < -10 && !_flipped)
	{

		_flipped = true;
		this->setFlippedY(true);
	
	}	
	if (water != nullptr)
	{
		if (this->getPositionY() < water->getPositionY())
		{
			water->setOpacity(255);
			water->runAction(Sequence::create(_water_splash->get()->clone(),RemoveSelf::create(),nullptr));
			isDelete = true;
			this->setVisible(false);
			this->runAction(Sequence::create(DelayTime::create(1.5), RemoveSelf::create(), nullptr));
		}
	}
	
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
		if (this->getPosition().x - _mSonic->getPosition().x < 1500) //Fix when move scene, Monster move wrong position
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
		_currentAnimate = _fightAni;
		_currentAction = RepeatForever::create(_currentAnimate->get()->clone());
		this->getPhysicsBody()->setCollisionBitmask(0);
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
