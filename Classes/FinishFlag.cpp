#include "FinishFlag.h"



FinishFlag::FinishFlag()
{
	this->autorelease();
	this->initWithFile("Item/finish-flag.png", Rect(307, 155, 132, 131));
	this->setPosition(100, 100);
	end = new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(Define::loadAnim("Item/finish-flag.xml", "1"), 0.035f)));
	//this->runAction(Repeat::create(end->get(), 10));
	this->setAnchorPoint(Vec2(0.5, 0.5));

	auto body = PhysicsBody::createBox(Size(132, 131));
                              
	body->setDynamic(false);
	body->setGravityEnable(false);

	body->setCategoryBitmask(8); 
	body->setCollisionBitmask(0);  
	body->setContactTestBitmask(1);


	this->setPhysicsBody(body);
	this->setTag(Define::FINISH);
}


FinishFlag::~FinishFlag()
{
}

void FinishFlag::RunAnimation()
{
	this->runAction(Repeat::create(end->get(), 3));
	this->getPhysicsBody()->setContactTestBitmask(0);
}
