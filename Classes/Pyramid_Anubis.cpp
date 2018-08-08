#include "Pyramid_Anubis.h"

Pyramid_Anubis::Pyramid_Anubis()
{
	this->autorelease();
	this->initWithFile("Monster/Desert/Pyramid2.png");
	auto physic_body = PhysicsBody::createCircle(this->getContentSize().width / 2);
	//physic_body->setRotationEnable(true);
	//physic_body->setMass(210);

	physic_body->setCategoryBitmask(16);    // 0010
	physic_body->setCollisionBitmask(0);   // 0001
	physic_body->setContactTestBitmask(1);

	this->setPhysicsBody(physic_body);
	this->setTag(Define::PYRAMID);
}


Pyramid_Anubis::~Pyramid_Anubis()
{
}

void Pyramid_Anubis::ComeBack()
{
	auto destroy_anubis = CallFunc::create([this]()
	{
		auto mon = (AnubisMonster*)_pyramid;
		mon->SetStateByTag(DIE);
		//khi->runAction(RemoveSelf::create());
	});
	this->runAction(Sequence::create(MoveTo::create(0.3, _pyramid->getPosition() + Vec2(0, 70)), destroy_anubis, RemoveSelf::create(), nullptr));

}
