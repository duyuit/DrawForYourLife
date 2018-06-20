#include "Sonic.h"



Sonic::Sonic()
{
	Vector<SpriteFrame*> run_slow_FL = loadAnim("sonic_animation.xml", "run_slow");
	Vector<SpriteFrame*> run_normal_FL = loadAnim("sonic_animation.xml", "run_normal");
	Vector<SpriteFrame*> run_fast_FL = loadAnim("sonic_animation.xml", "run_fast");

	


	run_fast_Ani = new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(run_fast_FL, 0.01f)));
	run_slow_Ani = new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(run_slow_FL, 0.1f)));
	run_normal_Ani = new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(run_normal_FL, 0.07f)));


	auto ballBody = PhysicsBody::createBox(Size(117,151)); // Tạo 1 khung body có đặc tính vật lý để phát hiện va chạm, khung này dạng tròn có đường kính = nội dung của _ball chia 2.
	ballBody->getShape(0)->setRestitution(0);
	ballBody->setContactTestBitmask(0x1); // Cái này rất quan trọng, nếu ko có thì hàm onContactBegin ko có tác dụng, tìm trên mạng mãi mới sửa được lỗi này


	this->setPhysicsBody(ballBody);

	this->initWithSpriteFrame(run_slow_FL.at(0));
	this->setPosition(200, 100);
	this->setAnchorPoint(Vec2(0.5f, 0));
	ballBody->setPositionOffset(Vec2(117/4, 151/4));
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
	int delta_y = end.y - end.y;
	bool isLeft_temp=false;
	if (delta_x > 200)
	{
		cur_Swipe_direction = Define::SWIPE_DIRECTION::RIGHT;
		isLeft_temp = false;
	}
	if (delta_x < -200)
	{
		cur_Swipe_direction = Define::SWIPE_DIRECTION::LEFT;
		isLeft_temp = true;
	}

	if (delta_y > 200) 
		cur_Swipe_direction = Define::SWIPE_DIRECTION::DOWN;
	if (delta_y <-200) 
		cur_Swipe_direction = Define::SWIPE_DIRECTION::UP;
	mCurrentState->handle_swipe(cur_Swipe_direction);
	isLeft = isLeft_temp;
	
	
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
	}
	this->runAction(mCurrentAction);
}
