#include "Sonic.h"



Sonic::Sonic()
{
	Vector<SpriteFrame*> run_slow_FL = loadAnim("sonic_animation.xml", "run_slow");
	Vector<SpriteFrame*> run_normal_FL = loadAnim("sonic_animation.xml", "run_normal");
	Vector<SpriteFrame*> run_fast_FL = loadAnim("sonic_animation.xml", "run_fast");
	Vector<SpriteFrame*> jump_FL = loadAnim("sonic_animation.xml", "jump");
	Vector<SpriteFrame*> roll_FL = loadAnim("sonic_animation.xml", "roll");


	run_fast_Ani = new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(run_fast_FL, 0.01f)));
	run_slow_Ani = new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(run_slow_FL, 0.1f)));
	run_normal_Ani = new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(run_normal_FL, 0.07f)));
	jump_Ani= new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(jump_FL, 0.03f)));
	roll_Ani=new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(roll_FL, 0.03f)));

	auto verti = PhysicsBody::createBox(Size(117,151));
	verti->setContactTestBitmask(0x1);
	verti->setRotationEnable(false);
	verti->setDynamic(true);
	
	verti->getShape(0)->setRestitution(0.0f);//đàn hồi
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
	SetStateByTag(SonicState::StateAction::RUN_SLOW);
	this->setFlipX(true);

	
}


Sonic::~Sonic()
{
}

void Sonic::update()
{
	
	this->setFlippedX(!isLeft);
	mCurrentState->update();
	this->setPosition(this->getPosition() + velocity);
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

Vector<SpriteFrame*> Sonic::loadAnim(char * path, std::string key)
{
	Vector<SpriteFrame*> list;

	tinyxml2::XMLDocument xml_doc;
	tinyxml2::XMLError eResult = xml_doc.LoadFile(path);

	tinyxml2::XMLElement* root = xml_doc.RootElement();
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


				list.pushBack(SpriteFrame::create(child->Attribute("imagePath"), Rect(x, y, w, h)));

				ele = ele->NextSiblingElement();
			}
			break;
		}
		child = child->NextSiblingElement();
	}

	


	return list;
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
	}
	this->runAction(mCurrentAction);
}
