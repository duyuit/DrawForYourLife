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
	plane->setPosition(pos+Vec2(1000,1000));
	plane->runAction(Sequence::create(
		MoveTo::create(5, pos+Vec2(110,50 + 300)),
		DelayTime::create(0.4),
		MoveBy::create(2,Vec2(0,-300)),
		DelayTime::create(0.3),
		active_car,
		nullptr));

	layer->addChild(drill,10);
	layer->addChild(plane,9);
}


BossLv1::~BossLv1()
{
}

void BossLv1::Merge()
{
}
