#include "BossDrill.h"



BossDrill::BossDrill()

{
	car = Sprite::create("Monster/Boss/car.png",Rect(0,0,434,184));
	car->setAnchorPoint(Vec2(0, 1));

	drill = Sprite::create("Monster/Boss/drill.png", Rect(8, 0, 140, 105));
	drill->setAnchorPoint(Vec2(0, 1));


	drill_anim = new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(Define::loadAnim("Monster/Boss/drill.xml", "run"), 0.02f)));
	car_anim = new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(Define::loadAnim("Monster/Boss/car.xml", "run"), 0.04f)));
	
	
	car->setPosition(0, 0);
	drill->setPosition(-50, -45);

	this->addChild(car);
	this->addChild(drill);

	this->setScale(0.7);
}


BossDrill::~BossDrill()
{
}

void BossDrill::ActiveDrill()
{
	car->runAction(RepeatForever::create(car_anim->get()));
	drill->runAction(RepeatForever::create(drill_anim->get()));
}
