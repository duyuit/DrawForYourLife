#include "LandMonster.h"



LandMonster::LandMonster()
{


	move_ani = new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(Define::loadAnim("monster.xml","move"), 0.05f)));
	//run_slow_Ani = new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(run_slow_FL, 0.1f)));
	

	auto verti = PhysicsBody::createBox(Size(30, 30));
	verti->setCategoryBitmask(0x02);    // 0010
	verti->setCollisionBitmask(0x02);   // 0001
	verti->setContactTestBitmask(0x1);

	verti->setRotationEnable(false);
	verti->setDynamic(true);
	verti->setGravityEnable(false);
	verti->getShape(0)->setRestitution(0.0f);//đàn hồi
	this->setPhysicsBody(verti);


	this->init();

	//this->setScale(1.5);
	this->setAnchorPoint(Vec2(0.5f, 1));
	verti->setPositionOffset(Vec2(30 / 4, 30 / 4));
	this->setFlipX(true);
	this->runAction(RepeatForever::create(move_ani->get()));
	this->setTag(Define::land_monster);
	this->scheduleUpdate();
}


LandMonster::~LandMonster()
{
}

void LandMonster::update(float dt)
{
	if (count_to_move == 60)
	{
		this->setFlipX(!this->isFlipX());
		velocity.x *= -1;
		count_to_move = 0;
	}
	count_to_move++;
	this->setPosition(this->getPosition() + velocity);
}
