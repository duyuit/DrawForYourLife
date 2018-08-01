#include "BossLv1.h"



BossLv1::BossLv1(Vec2 pos, Layer* layer)
{
	drill = new BossDrill();
	plane = new BossPlane();

	drill->setPosition(pos);
	

	auto active_car = CallFunc::create([this]()
	{
		drill->ActiveDrill();
		plane->ActiveWing(false);
	});
	plane->setPosition(pos+Vec2(500,500));


	
	plane->runAction(Sequence::create(
		MoveTo::create(2, pos+Vec2(110,50 + 300)),
		DelayTime::create(0.4),
		MoveBy::create(2,Vec2(0,-300)),
		DelayTime::create(0.3),
		active_car,
		nullptr));
	this->scheduleUpdate();
	layer->addChild(drill,10);
	layer->addChild(plane,9);
}


BossLv1::~BossLv1()
{
}

void BossLv1::SetState(STATE state)
{
	switch (state)
	{
	case BossLv1::RUN:
		if (isLeft)
		{
			drill->runAction(Sequence::create(MoveBy::create(3, Vec2(-1500, 0)),FlipX::create(true),MoveBy::create(3,Vec2(1500,0)),NULL));
			plane->runAction(Sequence::create(MoveBy::create(3, Vec2(-1500, 0)), FlipX::create(true), MoveBy::create(3, Vec2(1500, 0)), NULL));
		}
		else
		{
			auto flip = CallFunc::create([this]() {
				drill->Flip(true);
				plane->Flip(true);
			});
			auto flip2 = CallFunc::create([this]() {
				drill->Flip(false);
				plane->Flip(false);
			});
			drill->runAction(Sequence::create(
				MoveBy::create(5, Vec2(-1500, 0)), 
				flip, 
				MoveBy::create(5, Vec2(1800, 0)),
				flip2,
				MoveBy::create(1,Vec2(-300,0)),
				NULL));
			plane->runAction(Sequence::create(
				MoveBy::create(5, Vec2(-1500, 0)),
				MoveBy::create(5, Vec2(1800, 0)), 
				flip2,
				MoveBy::create(1, Vec2(-300, 0)),
				NULL));
		}
		break;
	case BossLv1::FIGHT:
		drill->FireDrill();
		break;
	default:
		break;
	}
}

void BossLv1::update(float dt)
{
	//count_to_change_state++;
	//if (count_to_change_state == 60*6)
	//{
	////	count_to_change_state = 0;
	//	SetState(RUN);
	//}
}

void BossLv1::Merge()
{
}

void BossLv1::Flip()
{
	//drill->Flip();

}
