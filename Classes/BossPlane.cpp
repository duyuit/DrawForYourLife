#include "BossPlane.h"



BossPlane::BossPlane()
{

	back = Sprite::create("Monster/Boss/helicopter.png", Rect(229, 33, 207, 191));
	back->setAnchorPoint(Vec2(0, 1));
	back->setPosition(0, 0);

	face = Sprite::create("Monster/Boss/eggman.png", Rect(51, 68, 129, 57));
	face->setAnchorPoint(Vec2(0, 1));
	face->setPosition(17,-14);



	front = Sprite::create("Monster/Boss/helicopter.png", Rect(20, 51, 151, 148));
	front->setAnchorPoint(Vec2(0,1));
	front->setPosition(-46, -26);


	
	wing = Sprite::create("Monster/Boss/wing.png", Rect(0, 0, 408, 36));
	//wing->setAnchorPoint(Vec2(0.91, 0.783));
	wing->setAnchorPoint(Vec2(0.5,0));
	wing->setPosition(100, 0);


	back_anim = new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(Define::loadAnim("Monster/Boss/plane.xml","1"), 0.01f)));
	normal_face = new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(Define::loadAnim("Monster/Boss/boss_face.xml", "normal"), 0.03f)));
	angry_face = new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(Define::loadAnim("Monster/Boss/boss_face.xml", "angry"), 0.03f)));
	die_face = new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(Define::loadAnim("Monster/Boss/boss_face.xml", "die"), 0.03f)));
	turn_off_wing= new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(Define::loadAnim("Monster/Boss/wing.xml", "turnoff"),0.3)));
	normal_wing = new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(Define::loadAnim("Monster/Boss/wing.xml", "normal"), 0.06f)));
	turn_on_wing = new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(Define::loadAnim("Monster/Boss/wing.xml", "turnon"),0.3f)));
	wing->runAction(RepeatForever::create(normal_wing->get()));
	
	
	this->addChild(back, -1);
	this->addChild(face, 0);
	this->addChild(front, 1);
	this->addChild(wing,-2);

	this->setScale(0.7);
	this->scheduleUpdate();

	//ActiveWing(true);
}


BossPlane::~BossPlane()
{
}

void BossPlane::ActiveWing(bool on)
{
	wing->stopAllActions();
	if (on)
	{
	//	wing->runAction(MoveBy::create(1, Vec2(0, 50)));
		wing->runAction(turn_on_wing->get());
	}
	else
	{
		wing->runAction(Sequence::create(turn_off_wing->get(), MoveBy::create(1, Vec2(0, -50)), nullptr));
		/*wing->runAction(turn_off_wing->get());
		wing->runAction(MoveBy::create(1, Vec2(0, -50)));*/
	}
}

void BossPlane::update(float dt)
{
	//if (isOn && turn_on_wing->get()->getCurrentFrameIndex() == 6)
	//{
	//	wing->runAction(RepeatForever::create(normal_wing->get()));
	//}
	

	//count_to_roll_wing++;
	//if (count_to_roll_wing == 120)
	//{
	//	count_to_roll_wing = 0;
	//	test = !test;
	//	ActiveWing(test);

	//}
}