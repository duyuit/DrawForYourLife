#include "Coconut_Monkey.h"


#include "MonkeyMonster.h"
Coconut_Monkey::Coconut_Monkey()
{
	this->initWithFile("Monster/Coconut.png");
	auto physic_body = PhysicsBody::createCircle(this->getContentSize().width / 2);
	physic_body->setRotationEnable(true);
	physic_body->setMass(210);

	physic_body->setCategoryBitmask(16);    // 0010
	physic_body->setCollisionBitmask(0);   // 0001
	physic_body->setContactTestBitmask(1);

	this->setPhysicsBody(physic_body);
	this->setTag(Define::COCONUT);



}


Coconut_Monkey::~Coconut_Monkey()
{
}

void Coconut_Monkey::ComeBack()
{
	auto destroy_monkey = CallFunc::create([this]()
	{
		auto mon = (MonkeyMonster*)khi;
		mon->SetStateByTag(DIE);
		//khi->runAction(RemoveSelf::create());
	});
	this->runAction(Sequence::create(MoveTo::create(0.3,khi->getPosition()),destroy_monkey,RemoveSelf::create(),nullptr));

}

void Coconut_Monkey::disableButton()
{
	auto mon = (MonkeyMonster*)khi;
	mon->disableButton();

}
