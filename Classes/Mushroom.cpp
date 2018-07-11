#include "Mushroom.h"


#include "GameDefine.h"
Mushroom::Mushroom()
{
	this->initWithFile("Item/mushroom.png", Rect(235, 1249, 121, 64));
	push_Ani = new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(Define::loadAnim("Item/mushroom.xml","1"), 0.02f)));
	this->setTag(Define::MUSHROOM);
	this->setAnchorPoint(Vec2(0.5, 0));
	auto body = PhysicsBody::createBox(this->getContentSize());

	//body->getShape(0)->setFriction(1.0f);                                    
	body->getShape(0)->setDensity(0.05f);
	body->setDynamic(false);
	body->setGravityEnable(false);
	body->setRotationEnable(false);

	body->setCategoryBitmask(8);    // 0010
	body->setCollisionBitmask(0);   // 0001
	body->setContactTestBitmask(1);


	this->setPhysicsBody(body);

}


Mushroom::~Mushroom()
{
}

void Mushroom::Active()
{
	if (!_isActive)
	{
		this->runAction(push_Ani->get());
		_isActive = true;
	}
}
