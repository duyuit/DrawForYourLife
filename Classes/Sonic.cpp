#include "Sonic.h"



Sonic::Sonic()
{
	Vector<SpriteFrame*> run_slow_FL = loadAnim("Sonic/sonic_animation.xml", "run_slow");
	Vector<SpriteFrame*> run_normal_FL = loadAnim("Sonic/sonic_animation.xml", "run_normal");
	Vector<SpriteFrame*> run_fast_FL = loadAnim("Sonic/sonic_animation.xml", "run_fast");
	Vector<SpriteFrame*> jump_FL = loadAnim("Sonic/sonic_animation.xml", "jump");
	Vector<SpriteFrame*> roll_FL = loadAnim("Sonic/sonic_animation.xml", "roll");
	Vector<SpriteFrame*> fall_FL = loadAnim("Sonic/sonic_animation.xml", "fall");
	Vector<SpriteFrame*> hurt_FL = loadAnim("Sonic/sonic_animation.xml", "hurt");

	run_fast_Ani = new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(run_fast_FL, 0.01f)));
	run_slow_Ani = new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(run_slow_FL, 0.1f)));
	run_normal_Ani = new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(run_normal_FL, 0.07f)));
	jump_Ani= new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(jump_FL, 0.03f)));
	roll_Ani=new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(roll_FL, 0.03f)));
	fall_Ani= new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(fall_FL, 0.01f)));
	roll_sky_Ani= new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(loadAnim("Sonic/sonic_animation.xml", "roll_in_sky"), 0.03f)));;
	hurt_Ani= new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(hurt_FL, 0.05f)));


	auto verti = PhysicsBody::createCircle(75, PhysicsMaterial(0.1f, 0.0f, 0.0f));

	verti->setCategoryBitmask(1);    // 0010
	verti->setCollisionBitmask(6);   // 0001
	verti->setContactTestBitmask(30);

	verti->setRotationEnable(false);
	verti->setDynamic(true);
	
	//verti->getShape(0)->setRestitution(0.0f);//đàn hồi
	this->setPhysicsBody(verti);


	this->initWithSpriteFrame(run_slow_FL.at(0));
	this->setPosition(200, 100);
	this->setAnchorPoint(Vec2(0.5f, 0));
	verti->setPositionOffset(Vec2(117 / 4, 151 / 4));
	this->setScale(0.5f);


	this->mData = new SonicData();
	this->mData->player = this;
	mCurrentState = new SonicRunSlowState(mData);
	mCurrentAnimate = run_slow_Ani;
	mCurrentAction = mCurrentAnimate->get();
	SetStateByTag(SonicState::StateAction::RUN_FAST);
	this->setFlipX(true);
	this->setTag(Define::Player);


	
	scheduleOnce(CC_SCHEDULE_SELECTOR(Sonic::updateStart), 0);
	this->scheduleUpdate();
	
}


Sonic::~Sonic()
{
}
int count_to_reset_just_tap = 0;
void Sonic::update(float dt)
{

	SpriteFrame* sprite_frame = mCurrentAnimate->get()->getAnimation()->getFrames().at(mCurrentAnimate->get()->getCurrentFrameIndex())->getSpriteFrame();
	Sprite* sprite = Sprite::createWithSpriteFrame(sprite_frame);
	sprite->setScale(0.5f);
	sprite->setFlipX(!isLeft);
	sprite->setAnchorPoint(Vec2(0.5, 0));
	sprite->setPosition(getPosition());
	this->getParent()->addChild(sprite);
	sprite->setOpacity(100);
	sprite->runAction(Sequence::create(FadeTo::create(1.5,0), RemoveSelf::create(), NULL));

	count_to_reset_just_tap++;
	this->setFlippedX(!isLeft);
	if (dust!=nullptr)
	{
		if (mCurrentState->GetState() == SonicState::RUN_FAST || mCurrentState->GetState() == SonicState::ROLL)
			dust->setVisible(true);
		else dust->setVisible(false);
		dust->setFlippedX(isLeft);
		if (isLeft)
		{
			dust->setAnchorPoint(Vec2(0, 0));
			dust->setPosition(this->getPosition() + Vec2(5, 0));
		}
		else
		{
			dust->setAnchorPoint(Vec2(1, 0));
			dust->setPosition(this->getPosition() + Vec2(-5, 0));
		}
	}


	mCurrentState->update();
	if (GetVelocity().y < -5 && mCurrentState->GetState() != SonicState::StateAction::FALL)
		this->SetStateByTag(SonicState::StateAction::FALL);
	if (count_to_reset_just_tap == 20)
	{
		count_to_reset_just_tap = 0;
		mJustTap = NONE;
	}
}

void Sonic::handle_swipe(Vec2 start, Vec2 end)
{

	/*int delta_x = end.x - start.x;
	int delta_y = end.y - start.y;

	if (delta_x > 200)
	{
		cur_Swipe_direction = Define::SWIPE_DIRECTION::RIGHT;
		isLeft = false;
	}
	if (delta_x < -200)
	{
		cur_Swipe_direction = Define::SWIPE_DIRECTION::LEFT;
		isLeft = true;
	}

	if (delta_y > 200) `
		cur_Swipe_direction = Define::SWIPE_DIRECTION::UP;
	if (delta_y < -200)
	{
		cur_Swipe_direction = Define::SWIPE_DIRECTION::DOWN;
		SetStateByTag(SonicState::ROLL);
		return;
	}
	mCurrentState->handle_swipe(cur_Swipe_direction);*/

	
	
}

bool Sonic::CheckLastFrame()
{
	if (mCurrentAnimate->get()->getCurrentFrameIndex() == mCurrentAnimate->get()->getAnimation()->getFrames().size() - 1) 
		return true;
	return false;
}


void Sonic::SetStateByTag(SonicState::StateAction action)
{
	switch (action)
	{
	case SonicState::RUN_SLOW:
		this->SetState(new SonicRunSlowState(mData));
		break;
	case SonicState::RUN_NORMAL:
		this->SetState(new SonicRunNormalState(mData));
		break;
	case SonicState::RUN_FAST:
		this->SetState(new SonicRunFastState(mData));
		break;
	case SonicState::JUMP:
		this->SetState(new SonicJumpState(mData));
		break;
	case SonicState::ROLL:
		this->SetState(new SonicRollState(mData));
		break;
	case SonicState::FALL:
		this->SetState(new SonicFallState(mData));
		break;
	case SonicState::HOLD:
		this->SetState(new SonicHoldState(mData));
		break;
	case SonicState::HURT:
		this->SetState(new SonicHurtState(mData));
		break;

	}
}

void Sonic::SetState(SonicState * state)
{
	if (mCurrentState != NULL && mCurrentState != nullptr)
		delete mCurrentState;
	mCurrentState = state;

	this->stopAction(mCurrentAction);

	switch (mCurrentState->GetState())
	{
	case SonicState::RUN_SLOW:

		mCurrentAnimate = run_slow_Ani;
		mCurrentAction = RepeatForever::create(mCurrentAnimate->get());
		break;
	case SonicState::RUN_NORMAL:
		mCurrentAnimate = run_normal_Ani;
		mCurrentAction = RepeatForever::create(mCurrentAnimate->get());
		break;
	case SonicState::RUN_FAST:
		mCurrentAnimate = run_fast_Ani;
		mCurrentAction = RepeatForever::create(mCurrentAnimate->get());
		break;
	case SonicState::JUMP:
		mCurrentAnimate = jump_Ani;
		mCurrentAction = mCurrentAnimate->get()->clone();
		break;
	case SonicState::ROLL:
		mCurrentAnimate = roll_Ani;
		mCurrentAction = mCurrentAnimate->get();
		break;
	case SonicState::FALL:
		mCurrentAnimate = fall_Ani;
		mCurrentAction = mCurrentAnimate->get()->clone();
		break;
	case SonicState::HOLD:
		this->stopAllActions();
		//mCurrentState = nullptr;
		this->setTextureRect(Rect(1366, 1784, 132, 159));
		return;
		break;
	case SonicState::HURT:
		this->stopAllActions();
		mCurrentAnimate = hurt_Ani;
		mCurrentAction = mCurrentAnimate->get()->clone();
		break;
	}
	this->runAction(mCurrentAction);
}

//void Sonic::AddLightning()
//{
//	//lightning = Sprite::create();
//	//auto ani = Animate::create(Animation::createWithSpriteFrames(Define::loadAnim("particle.xml", "lightning"), 0.08f));
//	//lightning->runAction(RepeatForever::create(ani));
//	//lightning->setPosition(this->getPosition() + Vec2(-15, 10));
//	////lightning->setScale(0.5f);
//	//lightning->setAnchorPoint(Vec2(1.0f, 0));
//	//this->getParent()->addChild(lightning);
//
//
//	//lightning2= Sprite::create();
//	//auto ani1 = Animate::create(Animation::createWithSpriteFrames(Define::loadAnim("particle.xml", "lightning"), 0.1f));
//	//lightning2->runAction(RepeatForever::create(ani1));
//	//lightning2->setPosition(this->getPosition() + Vec2(-15, 5));
//	////lightning->setScale(0.5f);
//	//lightning2->setAnchorPoint(Vec2(1.0f, 0));
//	//this->getParent()->addChild(lightning2);
//
//}

Vec2 Sonic::GetVelocity()
{
	return this->getPhysicsBody()->getVelocity();
}

void Sonic::HandleCollision(Sprite * sprite)
{
	if (sprite->getTag() == Define::Ring)
	{
		MyParticle::CreateEatItem(sprite->getPosition(), (Layer*) this->getParent());
		sprite->runAction(RemoveSelf::create());
		ringCollected++;
	}
	
	//When Sonic hits enemy, push back and drop rings
	if (sprite->getTag() == Define::LANDMONSTER && mCurrentState->GetState() != SonicState::ROLL)
	{
		

		this->SetStateByTag(SonicState::HURT);
		this->runAction(Blink::create(2, 10));
		if (ringCollected > 0 && baseLife > 0)
		{
			int t = ringCollected; //Temp variable
			for (int i = 0; i < (int)(t / baseLife); i++)
			{
				runAction(CallFuncN::create(CC_CALLBACK_0(Sonic::DropRing, this)));
				//DropRing();
				 ringCollected--;
			}
			baseLife--;
		}
		else if ( ringCollected <= 0 || baseLife <= 0)
		{
			 ringCollected = 0;
			baseLife = 2;
		}
		//Monster cant collision with Sonic 
		sprite->getPhysicsBody()->setContactTestBitmask(0);
	
		
	}
	mCurrentState->HandleCollision(sprite);
}

void Sonic::SetVelocity(int x, int y)
{
	this->getPhysicsBody()->setVelocity(Vec2(x, y));
}

void Sonic::SetVelocityX(int x)
{
	this->getPhysicsBody()->setVelocity(Point(x, this->getPhysicsBody()->getVelocity().y));
}

void Sonic::DropRing()
{
	auto ring = new SmallRing();
	ring->setAnchorPoint(Vec2(0, 1));
	ring->setPosition(this->getPosition());
	ring->getPhysicsBody()->setDynamic(true);
	ring->getPhysicsBody()->setGravityEnable(true);

	ring->getPhysicsBody()->setCollisionBitmask(2);

	float x = RandomHelper::random_real(-1.0, 1.0);
	float y = RandomHelper::random_real(0.0, 10.0);

	ring->getPhysicsBody()->setVelocity(Vec2(0, 0));
	ring->getPhysicsBody()->applyForce(Vec2(-3000000 * x, 800000 * y));
	ring->getPhysicsBody()->setContactTestBitmask(1);
	ring->SetAutoRemove();

	this->getParent()->addChild(ring, 10);
}

void Sonic::updateStart(float dt)
{
	dust = Sprite::create();
	auto dust_anim = new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(loadAnim("Particle/particle.xml", "dust"), 0.05f)));;
	dust->runAction(RepeatForever::create(dust_anim->get()));
	dust->setScale(1.3);
	dust->setPosition(this->getPosition());
	this->getParent()->addChild(dust);

	/*_roll_circle = Sprite::create();
	_roll_circle->setAnchorPoint(Vec2(0.5, 0.5));
	_roll_circle->setScale(0.4);
	RefPtr<Animate>  *roll_circle_effect_Ani= new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(loadAnim("dash_circle.xml", "ai"), 0.005f)));
	_roll_circle->runAction(RepeatForever::create(roll_circle_effect_Ani->get()));*/

	_roll_effect = Sprite::create();
	_roll_effect->setScale(4,3);
	_roll_effect->setOpacity(150);
	_roll_effect->setAnchorPoint(Vec2(1, 0.5));
	RefPtr<Animate>  *roll_effect_Ani = new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(loadAnim("Sonic/dash.xml", "dash"), 0.01f)));;;;
	_roll_effect->runAction(RepeatForever::create(roll_effect_Ani->get()));

	//_roll_circle->setPosition(60,80);
	_roll_effect->setPosition(150,80);
	//this->addChild(_roll_circle);
	this->addChild(_roll_effect);
	_roll_effect->setVisible(false);
}
