#include "Sonic.h"

#include "TapButton.h"
#include "MultipleButton.h"
#include "FinishFlag.h"
#include "Monster.h"
#include "Coconut_Monkey.h"
Sonic::Sonic()
{
	this->autorelease();
	this->removeAllChildrenWithCleanup(true);
	this->removeAllComponents();
	this->removeFromParentAndCleanup(true);
	//Blue Sonic


	Vector<SpriteFrame*> run_fast_FL = sonic_loadAnim(false, "run_fast");
	Vector<SpriteFrame*> jump_FL = sonic_loadAnim(false, "jump");
	Vector<SpriteFrame*> roll_FL = sonic_loadAnim(false, "roll");
	Vector<SpriteFrame*> fall_FL = sonic_loadAnim(false, "fall");
	Vector<SpriteFrame*> hurt_FL = sonic_loadAnim(false, "hurt");
	Vector<SpriteFrame*> skip_FL = sonic_loadAnim(false, "run_skip");
	Vector<SpriteFrame*> roll_chest_FL = sonic_loadAnim(false, "roll_chest");
	//Red Sonic

	Vector<SpriteFrame*> run_fast_red_FL = sonic_loadAnim(true, "run_fast");
	Vector<SpriteFrame*> jump_red_FL = sonic_loadAnim(true, "jump");
	Vector<SpriteFrame*> roll_red_FL = sonic_loadAnim(true, "roll");
	Vector<SpriteFrame*> fall_red_FL = sonic_loadAnim(true, "fall");
	Vector<SpriteFrame*> hurt_red_FL = sonic_loadAnim(true, "hurt");
	Vector<SpriteFrame*> skip_red_FL = sonic_loadAnim(true, "run_skip");
	Vector<SpriteFrame*> roll_chest_red_FL = sonic_loadAnim(true, "roll_chest");
	//Blue Sonic Ani
	run_fast_Ani = new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(run_fast_FL, 0.01f)));

	jump_Ani= new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(jump_FL, 0.03f)));
	roll_Ani=new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(roll_FL, 0.03f)));
	fall_Ani= new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(fall_FL, 0.01f)));
	roll_sky_Ani= new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(sonic_loadAnim(false, "roll_boss"), 0.03f)));;
	hurt_Ani= new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(hurt_FL, 0.05f)));
	run_skip_Ani= new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(skip_FL, 0.05f)));
	roll_chest_Ani = new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(roll_chest_FL, 0.03f)));
	stop_Ani= new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(sonic_loadAnim(false, "stop"), 0.05f)));
	counter_Ani = new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(sonic_loadAnim(false, "counter"), 0.05f)));
	end_Ani= new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(sonic_loadAnim(false, "end"), 0.05f)));
	idle_Ani = new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(sonic_loadAnim(false, "idle"), 0.1f)));
	
	//Red Sonic Ani
	run_fast_red_Ani = new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(run_fast_red_FL, 0.01f)));
	jump_red_Ani = new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(jump_red_FL, 0.03f)));
	roll_red_Ani = new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(roll_red_FL, 0.03f)));
	fall_red_Ani = new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(fall_red_FL, 0.01f)));
	roll_sky_red_Ani = new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(sonic_loadAnim(true, "roll_boss"), 0.03f)));;
	hurt_red_Ani = new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(hurt_red_FL, 0.05f)));
	run_skip_red_Ani= new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(skip_red_FL, 0.05f)));
	roll_chest_red_Ani = new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(roll_chest_red_FL, 0.03f)));
	stop_red_Ani = new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(sonic_loadAnim(true, "stop"), 0.05f)));
	counter_red_Ani = new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(sonic_loadAnim(true, "counter"), 0.05f)));
	end_red_Ani = new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(sonic_loadAnim(true, "end"), 0.08f)));
	
	
	

	auto verti = PhysicsBody::createCircle(75, PhysicsMaterial(0.1f, 0.0f, 0.0f));

	verti->setCategoryBitmask(1);    // 0010
	verti->setCollisionBitmask(6);   // 0001
	verti->setContactTestBitmask(30);

	verti->setRotationEnable(false);
	verti->setDynamic(true);

	this->setPhysicsBody(verti);


	this->initWithSpriteFrame(run_fast_FL.at(0));
	this->setPosition(200, 100);
	this->setAnchorPoint(Vec2(0.5f, 0));
	verti->setPositionOffset(Vec2(117 / 4, 151 / 4));
	this->setScale(0.5f);

	this->mData = new SonicData();
	this->mData->player = this;
	mCurrentState = new SonicRunFastState(mData);
	mCurrentAnimate = run_fast_Ani;
	mCurrentAction = mCurrentAnimate->get();

	SetStateByTag(SonicState::StateAction::FALL);
	
	this->setFlipX(true);
	this->setTag(Define::Player);

	
	scheduleOnce(CC_SCHEDULE_SELECTOR(Sonic::updateStart), 0);
	this->scheduleUpdate();

	SwapAllAni();//Bug fix:Hao super Lag when Sonic change to red
	//autorelease();
}


Sonic::~Sonic()
{
}
int count_to_reset_just_tap = 0;
void Sonic::update(float dt)
{
	
	if (isDelete)
		return;
	//Set effects combo for Sonic 
	if (countCombo >= 5)
	{
		if (count_to_reset_just_tap % 5 == 0)
		{
			SpriteFrame* sprite_frame = mCurrentAnimate->get()->getAnimation()->getFrames().at(mCurrentAnimate->get()->getCurrentFrameIndex())->getSpriteFrame();
			Sprite* sprite = Sprite::createWithSpriteFrame(sprite_frame);
			sprite->setScale(0.5f);
			sprite->setFlipX(!isLeft);
			sprite->setAnchorPoint(Vec2(0.5, 0));
			sprite->setPosition(getPosition());
			this->getParent()->addChild(sprite);
			sprite->setOpacity(100);
			sprite->runAction(Sequence::create(FadeTo::create(0.8, 0), RemoveSelf::create(), NULL));
		}

		if (countCombo >= 10 && countCombo < 15)
		{
			if (!isRed)
			{
				_transform_red->setVisible(true);
				_transform_red->runAction(Sequence::create(FadeIn::create(0.1), _transform_red_Ani->get(), FadeOut::create(0.1), nullptr));
				//_transform_red->setVisible(false);
				
				SwapAllAni();
				isRed = true;
			}
		}
		else if (countCombo >= 15)
		{
			if (streak != nullptr)
				streak->setVisible(true);
			streak->setPosition(this->getPosition() + Vec2(10, 30));
		}

	}


	count_to_reset_just_tap++;
	this->setFlippedX(!isLeft);

	if (countCombo >= 0 && countCombo < 20)
	{
		if (dust != nullptr)
		{
			flame->setVisible(false);

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
	}
	else if (countCombo >= 20)
	{
		if (flame != nullptr)
		{
			dust->setVisible(false);

			if (mCurrentState->GetState() == SonicState::RUN_FAST || mCurrentState->GetState() == SonicState::ROLL)
				flame->setVisible(true);
			else flame->setVisible(false);
			flame->setFlippedX(isLeft);
			if (isLeft)
			{
				flame->setAnchorPoint(Vec2(0, 0));
				flame->setPosition(this->getPosition() + Vec2(5, 0));
			}
			else
			{
				flame->setAnchorPoint(Vec2(1, 0));
				flame->setPosition(this->getPosition() + Vec2(-5, 0));
			}
		}
	}


	mCurrentState->update();
	if(_roll_effect!=nullptr)
	if (mCurrentState->GetState() != SonicState::ROLL && mCurrentState->GetState() != SonicState::ROLL_CHEST && _roll_effect->isVisible())
		_roll_effect->setVisible(false);
	if (GetVelocity().y < -5 && mCurrentState->GetState() != SonicState::StateAction::FALL
		&& mCurrentState->GetState() != SonicState::StateAction::ROLL
		&& mCurrentState->GetState() != SonicState::StateAction::DIE
		&& mCurrentState->GetState() != SonicState::StateAction::RUNSKIP
		&& mCurrentState->GetState() != SonicState::StateAction::ROLL_IN_SKY)
		this->SetStateByTag(SonicState::StateAction::FALL);
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
	if (isDelete) return;
	switch (action)
	{
	case SonicState::IDLE:
		this->SetState(new SonicIdleState(mData));
		break;
	case SonicState::ROLL_IN_SKY:
		this->SetState(new SonicRollSky(mData));
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
	case SonicState::DIE:
		this->SetState(new SonicDieState(mData));
		break;
	case SonicState::RUNSKIP:
		this->SetState(new SonicRunSkipState(mData));
		break;
	case SonicState::ROLL_CHEST:
		this->SetState(new SonicRollChestState(mData));
		break;
	case SonicState::STOP:
		this->SetState(new SonicStopState(mData));
		break;
	case SonicState::COUNTER:
		this->SetState(new SonicCounterState(mData));
		break;
	case SonicState::END:
		this->SetState(new SonicEndState(mData));
		break;
	}
	
}

void Sonic::SetState(SonicState * state)
{
	if (isDelete) return;

	if (mCurrentState != NULL && mCurrentState != nullptr)
		delete mCurrentState;
	mCurrentState = state;

	this->stopAction(mCurrentAction);
	if (mCurrentState->GetState() != SonicState::HURT)
		this->getPhysicsBody()->setContactTestBitmask(30);

	switch (mCurrentState->GetState())
	{
	case SonicState::IDLE:
		mCurrentAnimate = idle_Ani;
		mCurrentAction = RepeatForever::create(mCurrentAnimate->get());
		break;

	case SonicState::ROLL_IN_SKY:
		mCurrentAnimate = roll_sky_Ani;
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
	case SonicState::HURT:
		//this->stopAllActions();
	{
		auto func = CallFunc::create([this]()
		{
			this->setVisible(true);
		});
		this->getPhysicsBody()->setContactTestBitmask(14);
		this->runAction(Sequence::create(Blink::create(3, 15), func, nullptr));
		mCurrentAnimate = hurt_Ani;
		mCurrentAction = mCurrentAnimate->get();
		break;
	}
	
	case SonicState::RUNSKIP:
		mCurrentAnimate = run_skip_Ani;
		mCurrentAction = RepeatForever::create(mCurrentAnimate->get());
		break;
	case SonicState::ROLL_CHEST:
		mCurrentAnimate = roll_chest_Ani;
		mCurrentAction = RepeatForever::create(mCurrentAnimate->get());
		break; 
	case SonicState::STOP:
			mCurrentAnimate = stop_Ani;
			mCurrentAction = mCurrentAnimate->get();
			break;
	case SonicState::COUNTER:
		mCurrentAnimate = counter_Ani;
		mCurrentAction = mCurrentAnimate->get();
		break;
	case SonicState::END:
		mCurrentAnimate = end_Ani;
		mCurrentAction = mCurrentAnimate->get();
		break;
	case SonicState::DIE:
		
		this->stopAllActions();
		this->getPhysicsBody()->removeFromWorld();
		
		/*auto restart_scene = CallFunc::create([this]()
		{
			this->isDelete = true;
		});*/
		auto over_scene = CallFunc::create([this]()
		{
			this->isGameOver = true;
		});

		mCurrentAction =  Sequence::create(JumpBy::create(1.5, Vec2(-200, -600), 200, 1), over_scene, nullptr);
		break;

	}
	if(mCurrentAction!=nullptr)
	this->runAction(mCurrentAction);
}

Vec2 Sonic::GetVelocity()
{
	return this->getPhysicsBody()->getVelocity();
}

void Sonic::HandleCollision(Sprite * sprite)
{

	if (sprite->getTag() == Define::Ring)
	{
		ringCollected++;

		MyParticle::CreateEatItem(sprite->getPosition(), (Layer*) this->getParent());
		sprite->runAction(RemoveSelf::create());
		//Play sound when eat rings
		Define::_music_eat_ring_effect = experimental::AudioEngine::play2d(Define::_music_eat_ring_effect_path, false, 0.8f);
	}
	else if (sprite->getTag() == Define::MUSHROOM /*&& (mCurrentState->GetState()== SonicState::FALL || mCurrentState->GetState() == SonicState::ROLL)*/)
	{
		auto mush_room = (Mushroom*)sprite;
		mush_room->Active();
		this->SetVelocity(0, 0);
		this->getPhysicsBody()->applyImpulse(Vec2(0, 200000));
		this->SetStateByTag(SonicState::JUMP);
		if (isLeft)
			SetVelocityX(-200);
		else
			SetVelocityX(200);
	}
	else if (sprite->getTag() == Define::CHEST && mCurrentState->GetState() == SonicState::ROLL)
	{
		this->SetStateByTag(SonicState::ROLL_CHEST);
		return;
	}
	else if (sprite->getTag() == Define::FINISH)
	{
		auto flag = (FinishFlag*)sprite;
		flag->RunAnimation();

		isFinish = true;
		this->SetStateByTag(SonicState::END);

		//Play finish music effect
		experimental::AudioEngine::stopAll();
		Define::_music_finish_level_effect = experimental::AudioEngine::play2d(Define::_music_finish_level_effect_path, false, 1.0f);		
		return;
	}
	else if (sprite->getTag() == Define::DIELAND && mCurrentState->GetState() != SonicState::DIE)
	{
		this->SetStateByTag(SonicState::DIE);
		return;
	}

	//When Sonic hits enemy, push back and drop rings
	else if ((sprite->getTag() == Define::LANDMONSTER || sprite->getTag() == Define::COCONUT) 
		&& mCurrentState->GetState() != SonicState::ROLL &&mCurrentState->GetState() != SonicState::COUNTER)
	{
		this->SetStateByTag(SonicState::HURT);

		//Bug fix: hurt but still can Active button
		DisableCurrentButton();

		//this->runAction(Sequence::create(DelayTime::create(1), Blink::create(2, 10), nullptr));
		//this->runAction(Blink::create(2, 10));
		
		if (ringCollected > 0)
		{
			Define::_music_drop_ring_effect = experimental::AudioEngine::play2d(Define::_music_drop_ring_effect_path);

			int t = ringCollected; //Temp variable
			for (int i = 0; i < (t / 2); i++)
			{
				runAction(CallFuncN::create(CC_CALLBACK_0(Sonic::DropRing, this)));
				ringCollected--;
			}
		}
		//Monster cant collision with Sonic 
		sprite->getPhysicsBody()->setContactTestBitmask(0);	
	}
	else if (sprite->getTag() == Define::DRILL)
	{
		this->SetStateByTag(SonicState::HURT);
		//this->runAction(Sequence::create(DelayTime::create(1), Blink::create(2, 10), nullptr));
		this->runAction(Blink::create(1, 4));
		
		if (ringCollected > 0)
		{
			Define::_music_drop_ring_effect = experimental::AudioEngine::play2d(Define::_music_drop_ring_effect_path);

			int t = ringCollected; //Temp variable
			for (int i = 0; i < (t / 2); i++)
			{
				runAction(CallFuncN::create(CC_CALLBACK_0(Sonic::DropRing, this)));
				ringCollected--;
			}
		}
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
	ring->setPosition(this->getPosition() + Vec2(0, 50));
	ring->getPhysicsBody()->setDynamic(true);
	ring->getPhysicsBody()->setGravityEnable(true);

	ring->getPhysicsBody()->setCollisionBitmask(2);
	ring->getPhysicsBody()->setContactTestBitmask(0);

	float x = RandomHelper::random_real(-1.0, 1.0);
	float y = RandomHelper::random_real(1.0, 10.0);

	ring->getPhysicsBody()->setVelocity(Vec2(0, 0));
	ring->getPhysicsBody()->applyForce(Vec2(-3000000 * x, 800000 * y));
	ring->SetAutoRemove(); 

	this->getParent()->addChild(ring, 10);
	//ring->getPhysicsBody()->setContactTestBitmask(1);	
}

void Sonic::updateStart(float dt)
{
	//Dust effect
	dust = Sprite::create();
	auto dust_anim = new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(loadAnim("Particle/particle.xml", "dust"), 0.05f)));;
	dust->runAction(RepeatForever::create(dust_anim->get()));
	dust->setScale(1.3);
	dust->setPosition(this->getPosition());
//	dust->setColor(Color3B(223, 85, 11));
	//dust->runAction(TintTo::create(0.1, Color3B(273,28,36)));
	this->getParent()->addChild(dust);

	//Flame effect
	flame = Sprite::create();
	auto flame_anim = new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(loadAnim("Particle/particle.xml", "flame"), 0.04f)));
	flame->runAction(RepeatForever::create(flame_anim->get()));
	flame->setScale(1.2);
	flame->setPosition(this->getPosition() + Vec2(25, 0));
	flame->setVisible(false);
	this->getParent()->addChild(flame, 100);

	/*_roll_circle = Sprite::create();
	_roll_circle->setAnchorPoint(Vec2(0.5, 0.5));
	_roll_circle->setScale(0.4);
	RefPtr<Animate>  *roll_circle_effect_Ani= new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(loadAnim("dash_circle.xml", "ai"), 0.005f)));
	_roll_circle->runAction(RepeatForever::create(roll_circle_effect_Ani->get()));*/

	_roll_effect = Sprite::create();
	_roll_effect->setScale(4,3);
	_roll_effect->setOpacity(150);
	_roll_effect->setAnchorPoint(Vec2(1, 0.5));
	RefPtr<Animate>  *roll_effect_Ani = new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(loadAnim("Sonic/dash.xml", "dash"), 0.01f)));
	_roll_effect->runAction(RepeatForever::create(roll_effect_Ani->get()));

	//_roll_circle->setPosition(60,80);
	_roll_effect->setPosition(150,80);
	//this->addChild(_roll_circle);
	this->addChild(_roll_effect);
	_roll_effect->setVisible(false);

	//Transform red effect
	_transform_red = Sprite::create();
	_transform_red->setScale(1, 1.8);
	_transform_red->setAnchorPoint(Vec2(1, 0.5));
	_transform_red_Ani = new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(loadAnim("Sonic/transform.xml", "1"), 0.025f)));
	_transform_red->runAction(RepeatForever::create(_transform_red_Ani->get()));
	_transform_red->setPosition(170, 70);
	this->addChild(_transform_red);
	_transform_red->setVisible(false);

	//Transform blue effect
	_transform_blue = Sprite::create();
	_transform_blue->setScale(1.5, 1.5);
	_transform_blue->setAnchorPoint(Vec2(0.5, 0.5));
	_transform_blue_Ani = new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(loadAnim("Sonic/transform.xml", "2"), 0.05f)));
	_transform_blue->runAction(RepeatForever::create(_transform_blue_Ani->get()));
	_transform_blue->setPosition(60, 80);
	this->addChild(_transform_blue);
	_transform_blue->setVisible(false);

	//MotionStreak
	streak = MotionStreak::create(2, 3, 60, Color3B::RED, "Particle/streak.png");
	streak->setAnchorPoint(Vec2(0, 0.5));
	streak->setVisible(false);
	this->getParent()->addChild(streak);
	auto colorAction = RepeatForever::create(Sequence::create(
		TintTo::create(0.2f, 255, 0, 0),
		TintTo::create(0.2f, 0, 255, 0),
		TintTo::create(0.2f, 0, 255, 255),
		TintTo::create(0.2f, 255, 255, 0),
		TintTo::create(0.2f, 255, 0, 255),
		TintTo::create(0.2f, 255, 255, 255),
		nullptr));
	streak->runAction(colorAction);	

	SwapAllAni(); //Bug fix:Hao super Lag when Sonic change to red
	
}

Vector<SpriteFrame*> Sonic::sonic_loadAnim(bool isRed,std::string key)
{
	Vector<SpriteFrame*> list;
	std::string path2 = FileUtils::getInstance()->getStringFromFile("Sonic/sonic_animation.xml");

	tinyxml2::XMLDocument *doc = new tinyxml2::XMLDocument();
	tinyxml2::XMLError eResult = doc->Parse(path2.c_str(), path2.size());

	tinyxml2::XMLElement* root = doc->RootElement();
	tinyxml2::XMLElement* child = root->FirstChildElement();
	while (child)
	{
		if (child->Attribute("name") == key)
		{
			tinyxml2::XMLElement* ele = child->FirstChildElement();
			while (ele)
			{
				float x;
				ele->QueryFloatAttribute("x", &x);
				float y;
				ele->QueryFloatAttribute("y", &y);
				float w;
				ele->QueryFloatAttribute("w", &w);
				float h;
				ele->QueryFloatAttribute("h", &h);

				if(isRed)
					list.pushBack(SpriteFrame::create("Sonic/99072_red.png", Rect(x, y, w, h)));
				else
					list.pushBack(SpriteFrame::create("Sonic/99072.png", Rect(x, y, w, h)));
				ele = ele->NextSiblingElement();
			}
			break;
		}
		child = child->NextSiblingElement();
	}

	return list;
}



void Sonic::SwapAni(RefPtr<Animate> *&blue, RefPtr<Animate> *&red)
{
	RefPtr<Animate> *x = blue;

	blue = red;
	red = x;
	x = nullptr;
}

void Sonic::SwapAllAni()
{
	SwapAni(run_fast_Ani, run_fast_red_Ani);

	SwapAni(jump_Ani, jump_red_Ani);
	SwapAni(roll_Ani, roll_red_Ani);
	SwapAni(fall_Ani, fall_red_Ani);
	SwapAni(roll_sky_Ani, roll_sky_red_Ani);
	SwapAni(hurt_Ani, hurt_red_Ani);
	SwapAni(run_skip_Ani, run_skip_red_Ani);
	SwapAni(roll_chest_Ani, roll_chest_red_Ani);
	SwapAni(stop_Ani, stop_red_Ani);
	SwapAni(counter_Ani, counter_red_Ani);
	SwapAni(end_Ani, end_red_Ani);
	
	this->SetStateByTag(mCurrentState->GetState());

	if (mCurrentState->GetState() == SonicState::JUMP || mCurrentState->GetState() == SonicState::ROLL_IN_SKY)
		this->getPhysicsBody()->applyForce(Vec2(0, -13500000)); //Fix jump so high when change to Red

	if (mCurrentState->GetState() == SonicState::ROLL_IN_SKY)
		this->getPhysicsBody()->applyForce(Vec2(0, -15500000));
}

void Sonic::DisableCurrentButton()
{
	if (mCurrentButton != nullptr)
	{
		if (isInMultipleButton)
		{
			MultipleButton* tap = (MultipleButton*)mCurrentButton;
			tap->DeleteNow(false);
		}
		else
		{
			TapButton* tap = (TapButton*)mCurrentButton;
			tap->DeleteNow(false);
		}

	}
}

void Sonic::ActiveButton(BUTTON_TAG dir)
{
	if (mCurrentState->GetState() == SonicState::DIE) return;
	mJustTap = dir;
	if (mCurrentButton != nullptr)
	{
		if (isInMultipleButton)
		{
			MultipleButton* tap = (MultipleButton*)mCurrentButton;
			tap->ActiveButton(dir);
		}
		else
		{
			TapButton* tap = (TapButton*)mCurrentButton;
			tap->ActiveButton(dir);
		}

	}




}
