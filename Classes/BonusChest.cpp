#include "BonusChest.h"
BonusChest::BonusChest(Sonic * sonic)
{
	_mSonic = sonic;

	this->initWithFile("Item/chest.png", Rect(11, 81, 126, 105));
	open_Ani = new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(Define::loadAnim("Item/chest.xml", "1"), 0.08f)));
	this->setTag(Define::CHEST);
	this->setAnchorPoint(Vec2(0.5, 0));
	this->setScale(0.8);
	auto body = PhysicsBody::createBox(this->getContentSize());

	//body->getShape(0)->setFriction(1.0f);  
	body->getShape(0)->setDensity(0.05f);
	body->setDynamic(false);
	body->setGravityEnable(false);
	body->setRotationEnable(false);

	body->setCategoryBitmask(8);    // 0010
	body->setCollisionBitmask(0);   // 0001
	body->setContactTestBitmask(1);
	
	this->setPhysicsBody(body);

	_multiButton = new MultipleButton(Vec2(0, 0), _mSonic, (Layer*)_mSonic->getParent(), 3, 2);
	this->scheduleUpdate();
}


void BonusChest::Open()
{
	_isCreateRing = false;
	this->runAction(Sequence::create(open_Ani->get(), FadeOut::create(1), RemoveSelf::create(), nullptr));
	//_mSonic->isActiveChest = false;
	//_mSonic->SetStateByTag(SonicState::RUN_FAST);
	//_isActive = false;
}

void BonusChest::CreateRing()
{
	auto ring = new SmallRing();
	ring->setAnchorPoint(Vec2(0, 1)); 
	ring->setPosition(this->getPosition() - Vec2(ring->getContentSize().width / 2, -ring->getContentSize().height / 1.2));
	ring->getPhysicsBody()->setDynamic(true);
	ring->getPhysicsBody()->setGravityEnable(false);

	ring->getPhysicsBody()->setCollisionBitmask(2);
	ring->getPhysicsBody()->setContactTestBitmask(0);

	float x = RandomHelper::random_real(-1.0, 1.0);
	float y = RandomHelper::random_real(0.0, 10.0);

	ring->getPhysicsBody()->setVelocity(Vec2(0, 0));
	ring->runAction(JumpBy::create(1, Vec2(-this->getContentSize().width / 2 - _mSonic->getContentSize().width / 4, 0), 300, 1));
	ring->getPhysicsBody()->setContactTestBitmask(1);
	ring->SetAutoRemove();

	this->getParent()->addChild(ring, 10);

	this->runAction(
			Repeat::create(
				Sequence::create(
					MoveBy::create(0.05f, Vec2(10, 0)),
					MoveBy::create(0.05f, Vec2(-10, 0)),
					MoveBy::create(0.012f, Vec2(0, 10)),
					MoveBy::create(0.012f, Vec2(0, -10)),
					nullptr), 2));

	this->runAction(
		Sequence::create(
			RotateTo::create(0.05f, -5),
			RotateTo::create(0.05f, 5),
			RotateTo::create(0.025f, 0), nullptr));
}

void BonusChest::update(float dt)
{
	_multiButton->setPosition(this->getPosition() + Vec2(-this->getContentSize().width/1.5, 150));

	if (_mSonic->mCurrentState->GetState() == SonicState::ROLL_CHEST)
	{	
		_isActive = true;
		if (_prev_tap != _mSonic->mJustTap && _prev_tap != NONE && _isCreateRing) CreateRing();
	}

	if (_isActive)
	{
		if (_time_to_open == 180) Open();
		if (_time_to_open == 240) _mSonic->SetStateByTag(SonicState::RUN_FAST);
	}

	if (_isActive) _time_to_open++;
	_prev_tap = _mSonic->mJustTap;
}

BonusChest::~BonusChest()
{
}