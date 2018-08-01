#include "BossDrill.h"



BossDrill::BossDrill()

{
	front_car = Sprite::create("Monster/Boss/front_car.png",Rect(0,0,374,184));
	front_car->setAnchorPoint(Vec2(0, 1));

	back_car= Sprite::create("Monster/Boss/back_car.png", Rect(0, 0, 60, 184));
	back_car->setAnchorPoint(Vec2(0, 1));

	drill = Sprite::create("Monster/Boss/drill.png", Rect(8, 0, 140, 105));
	drill->setAnchorPoint(Vec2(0, 1));
	drill->setTag(Define::DRILL);

	drill_anim = new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(Define::loadAnim("Monster/Boss/drill.xml", "run"), 0.02f)));
	car_anim = new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(Define::loadAnim("Monster/Boss/car.xml", "run"), 0.04f)));
	
	
	back_car->setPosition(0, 0);
	front_car->setPosition(back_car->getContentSize().width, 0);

	drill->setPosition(-50, -45);

	auto drill_body = PhysicsBody::createBox(drill->getContentSize());
	drill_body->setGravityEnable(false);
	drill_body->setCategoryBitmask(16);
	drill_body->setContactTestBitmask(1);
	drill_body->setCollisionBitmask(0);
	drill->setPhysicsBody(drill_body);

	this->addChild(front_car);
	this->addChild(back_car,-1);
	this->addChild(drill);

	this->setScale(0.7);


	 chain1 = Sprite::create("Monster/Boss/chain.png");
	chain1->setAnchorPoint(Vec2(0, 0.5));
	chain1->setPosition(Vec2(30, -45 - drill->getContentSize().height / 2));
	 chain2 = Sprite::create("Monster/Boss/chain.png");
	chain2->setAnchorPoint(Vec2(0, 0.5));
	chain2->setPosition(Vec2(30, -45 - drill->getContentSize().height/2));

	chain3 = Sprite::create("Monster/Boss/chain.png");
	chain3->setAnchorPoint(Vec2(0, 0.5));
	chain3->setPosition(Vec2(30, -45 - drill->getContentSize().height / 2));



	this->addChild(chain1,-1);
	this->addChild(chain2,-1);
	this->addChild(chain3, -1);

	this->scheduleUpdate();
}


BossDrill::~BossDrill()
{
}

void BossDrill::update(float dt)
{
	count_to_generate_dust++;
	if (count_to_generate_dust == 20)
	{
		count_to_generate_dust = 0;
		GenerateDust();
	}
}

void BossDrill::GenerateDust()
{
	auto dust = Sprite::create();
	int a = RandomHelper::random_int(1, 2);
	Animate* anim;
	if(a==1)
		anim = Animate::create(Animation::createWithSpriteFrames(Define::loadAnim("Particle/particle.xml", "dust1"), 0.05));
	else
		anim = Animate::create(Animation::createWithSpriteFrames(Define::loadAnim("Particle/particle.xml", "dust2"), 0.05));
	dust->runAction(anim);
	dust->runAction(Sequence::create(DelayTime::create(0.3), RemoveSelf::create(),NULL));
	if(front_car->isFlipX())
		dust->setPosition(this->getPosition()+Vec2(50,0));
	else
		dust->setPosition(this->getPosition() +Vec2(front_car->getContentSize().width-90,5));
	this->getParent()->addChild(dust);
}

void BossDrill::Flip(bool isFlip)
{

	front_car->setFlipX(isFlip);
	back_car->setFlipX(isFlip);
	drill->setFlipX(isFlip);
	if (isFlip)
	{
		drill->setPosition(front_car->getContentSize().width+ drill->getContentSize().width/2 -30, -45);
		back_car->setPosition(front_car->getContentSize().width+back_car->getContentSize().width, 0);
	}
	else
	{
		drill->setPosition(-50, -45);
		back_car->setPosition(0, 0);
	}
}

void BossDrill::ActiveDrill()
{
	front_car->runAction(RepeatForever::create(car_anim->get()));
	drill->runAction(RepeatForever::create(drill_anim->get()));
}

void BossDrill::FireDrill()
{

	int delta_posx = chain1->getContentSize().width;
	float delta = 0.666666;
	drill->runAction(MoveBy::create(2, Vec2(-delta_posx * 3 + 100, 0)));
	auto return_drill = CallFunc::create(CC_CALLBACK_0(BossDrill::ReturnDrill, this));
	chain1->runAction(MoveBy::create(2, Vec2(-delta_posx * 3 + 100, 0)));
	chain2->runAction(Sequence::create(DelayTime::create(delta), MoveBy::create(delta * 2, Vec2(-delta_posx * 2 + 100, 0)), NULL));
	chain3->runAction(Sequence::create(DelayTime::create(delta * 2), MoveBy::create(delta, Vec2(-delta_posx + 100, 0)), return_drill, NULL));

}

void BossDrill::ReturnDrill()
{
	int delta_posx = chain1->getContentSize().width;
	float delta = 0.666666;
	drill->runAction(MoveBy::create(2, Vec2(delta_posx * 3-100, 0)));
	chain1->runAction(MoveBy::create(2, Vec2(delta_posx *3 - 100,0)));
	chain2->runAction(MoveBy::create(delta*2, Vec2(delta_posx * 2 - 100, 0)));
	chain3->runAction(MoveBy::create(delta, Vec2(delta_posx - 100,0)));
}
