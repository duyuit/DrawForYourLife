#include "SmallRing.h"



SmallRing::SmallRing()
{
	this->init();
	this->setPosition(100, 100);
	roll = new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(Define::loadAnim("ring.xml", "roll"), 0.1f)));
	this->runAction(RepeatForever::create(roll->get()));
	this->setAnchorPoint(Vec2(0.5f, 0.5f));
	auto body = PhysicsBody::createBox(this->getContentSize());

	body->setDynamic(false);
	body->setGravityEnable(false);

	body->setCategoryBitmask(8);    // 0010
	body->setCollisionBitmask(0);   // 0001
	body->setContactTestBitmask(1);


	body->setRotationEnable(false);
	this->setPhysicsBody(body);
	this->setTag(Define::Ring);
}


SmallRing::~SmallRing()
{
}
