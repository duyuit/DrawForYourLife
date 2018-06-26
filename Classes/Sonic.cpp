#include "Sonic.h"



Sonic::Sonic()
{
	Vector<SpriteFrame*> run_slow_FL = loadAnim("sonic_animation.xml", "run_slow");
	Vector<SpriteFrame*> run_normal_FL = loadAnim("sonic_animation.xml", "run_normal");
	Vector<SpriteFrame*> run_fast_FL = loadAnim("sonic_animation.xml", "run_fast");
	Vector<SpriteFrame*> jump_FL = loadAnim("sonic_animation.xml", "jump");
	Vector<SpriteFrame*> roll_FL = loadAnim("sonic_animation.xml", "roll");
	Vector<SpriteFrame*> fall_FL = loadAnim("sonic_animation.xml", "fall");


	run_fast_Ani = new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(run_fast_FL, 0.01f)));
	run_slow_Ani = new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(run_slow_FL, 0.1f)));
	run_normal_Ani = new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(run_normal_FL, 0.07f)));
	jump_Ani= new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(jump_FL, 0.03f)));
	roll_Ani=new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(roll_FL, 0.03f)));
	fall_Ani= new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(fall_FL, 0.01f)));
	roll_sky_Ani= new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(loadAnim("sonic_animation.xml", "roll_in_sky"), 0.03f)));;

	auto verti = PhysicsBody::createBox(Size(117,151), PhysicsMaterial(0.1f, 0.0f, 0.0f));

	verti->setCategoryBitmask(1);    // 0010
	verti->setCollisionBitmask(6);   // 0001
	verti->setContactTestBitmask(14);

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


}


Sonic::~Sonic()
{
}

void Sonic::update()
{
	
	this->setFlippedX(!isLeft);
	
	mCurrentState->update();
	if (GetVelocity().y < -5 && mCurrentState->GetState() != SonicState::StateAction::FALL)
		this->SetStateByTag(SonicState::StateAction::FALL);
	/*if (lightning != nullptr && lightning2 != nullptr)
	{
		lightning->setPosition(this->getPosition() + Vec2(-15, 10));
		lightning2->setPosition(this->getPosition() + Vec2(-15,5));
	}*/

}

void Sonic::handle_swipe(Vec2 start, Vec2 end)
{

	int delta_x = end.x - start.x;
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

	if (delta_y > 200) 
		cur_Swipe_direction = Define::SWIPE_DIRECTION::UP;
	if (delta_y < -200)
	{
		cur_Swipe_direction = Define::SWIPE_DIRECTION::DOWN;
		SetStateByTag(SonicState::ROLL);
		return;
	}
	mCurrentState->handle_swipe(cur_Swipe_direction);

	
	
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
		mCurrentAction = mCurrentAnimate->get();
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
	}
	this->runAction(mCurrentAction);
}

void Sonic::AddLightning()
{
	//lightning = Sprite::create();
	//auto ani = Animate::create(Animation::createWithSpriteFrames(Define::loadAnim("particle.xml", "lightning"), 0.08f));
	//lightning->runAction(RepeatForever::create(ani));
	//lightning->setPosition(this->getPosition() + Vec2(-15, 10));
	////lightning->setScale(0.5f);
	//lightning->setAnchorPoint(Vec2(1.0f, 0));
	//this->getParent()->addChild(lightning);


	//lightning2= Sprite::create();
	//auto ani1 = Animate::create(Animation::createWithSpriteFrames(Define::loadAnim("particle.xml", "lightning"), 0.1f));
	//lightning2->runAction(RepeatForever::create(ani1));
	//lightning2->setPosition(this->getPosition() + Vec2(-15, 5));
	////lightning->setScale(0.5f);
	//lightning2->setAnchorPoint(Vec2(1.0f, 0));
	//this->getParent()->addChild(lightning2);

}

Vec2 Sonic::GetVelocity()
{
	return this->getPhysicsBody()->getVelocity();
}

void Sonic::handle_collision(Sprite * sprite)
{
	if (sprite->getTag() == Define::Ring)
	{
		MyParticle::CreateEatItem(sprite->getPosition(), (Layer*) this->getParent());
		sprite->runAction(RemoveSelf::create());
	}
	mCurrentState->handle_collision(sprite);
}

void Sonic::SetVelocity(int x, int y)
{
	this->getPhysicsBody()->setVelocity(Vec2(x, y));
}

void Sonic::SetVelocityX(int x)
{
	this->getPhysicsBody()->setVelocity(Point(x, this->getPhysicsBody()->getVelocity().y));
}
