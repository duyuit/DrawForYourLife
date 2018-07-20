#include "SmallRing.h"



SmallRing::SmallRing()
{
	this->initWithFile("Item/ring.png",Rect(0,0,50,50));
	this->setPosition(100, 100);
	roll = new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(Define::loadAnim("Item/ring.xml", "roll"), 0.1f)));
	this->runAction(RepeatForever::create(roll->get()));
	this->setAnchorPoint(Vec2(0.5, 0.5));
	
	auto body = PhysicsBody::createBox(Size(50,50));

	//body->getShape(0)->setFriction(1.0f);                                    
	body->getShape(0)->setDensity(0.05f);
	body->setDynamic(false);
	body->setGravityEnable(false);
	body->setRotationEnable(false);

	body->setCategoryBitmask(8);    // 0010
	body->setCollisionBitmask(0);   // 0001
	body->setContactTestBitmask(1);

	
	this->setPhysicsBody(body);
	this->setTag(Define::Ring);

}


SmallRing::~SmallRing()
{
}

void SmallRing::SetAutoRemove()
{

	this->runAction(Sequence::create(DelayTime::create(3), Blink::create(0.8, 5), RemoveSelf::create(), nullptr));
}
