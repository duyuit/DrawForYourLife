#include "HoldLand.h"



HoldLand::HoldLand(Vec2 pos,Size size, bool isLeft, Sonic* sonic, Layer* layer)
{
	this->init();
	//this->setVisible(false);

	this->setTag(Define::HoldPlace);

	

	this->setAnchorPoint(Vec2(0.5, 0.5));

	auto boundBody = PhysicsBody::createBox(Size(size));
	boundBody->getShape(0)->setFriction(10.0f);
	boundBody->setDynamic(false);
	boundBody->getShape(0)->setRestitution(100.0f);


	boundBody->setCategoryBitmask(4);
	boundBody->setCollisionBitmask(1);
	boundBody->setContactTestBitmask(1);
	this->setPhysicsBody(boundBody);

	this->setPosition(pos);

	_tapButton = new TapButton(pos, sonic, layer, !isLeft);
	
	if (isLeft)
		_tapButton->setPosition(_tapButton->getPosition() + Vec2(50, 100));
	else
		_tapButton->setPosition(_tapButton->getPosition() + Vec2(-50, 100));
	_tapButton->unscheduleUpdate();
	
	_tapButton->use_for_Hold = true;
	layer->addChild(this);
}

void HoldLand::Active()
{
	isActive = true;
	_tapButton->canActive = true;
	_tapButton->Active();
	_tapButton->scheduleUpdate();

}

HoldLand::~HoldLand()
{
}
