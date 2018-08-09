#include "BossPlane.h"


#include "GameParticle.h"
#include "BossLv1.h"
BossPlane::BossPlane()
{

	back = Sprite::create("Monster/Boss/helicopter.png", Rect(229, 33, 207, 191));
	back->setAnchorPoint(Vec2(0, 1));
	back->setPosition(0, 0);

	face = Sprite::create("Monster/Boss/eggman.png", Rect(51, 68, 129, 57));
	face->setAnchorPoint(Vec2(0, 0));
	face->setPosition(17,-14- face->getContentSize().height);
	face->setTag(Define::BOSS);

	auto face_body = PhysicsBody::createBox(face->getContentSize()+Size(100,0));
	face_body->setGravityEnable(false);
	face_body->setContactTestBitmask(1);
	face_body->setCollisionBitmask(0);
	face_body->setCategoryBitmask(2);
	face_body->setDynamic(false);
	face->setPhysicsBody(face_body);


	front = Sprite::create("Monster/Boss/helicopter.png", Rect(20, 51, 151, 148));
	front->setAnchorPoint(Vec2(0,1));
	front->setPosition(-46, -26);


	
	wing = Sprite::create("Monster/Boss/wing.png", Rect(0, 0, 408, 36));
	//wing->setAnchorPoint(Vec2(0.91, 0.783));
	wing->setAnchorPoint(Vec2(0.5,0));
	wing->setPosition(100, 0);


	back_anim = new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(Define::loadAnim("Monster/Boss/plane.xml","1"), 0.09f)));
	normal_face = new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(Define::loadAnim("Monster/Boss/boss_face.xml", "normal"), 0.09f)));
	angry_face = new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(Define::loadAnim("Monster/Boss/boss_face.xml", "angry"), 0.09f)));
	die_face = new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(Define::loadAnim("Monster/Boss/boss_face.xml", "die"), 0.09f)));
	turn_off_wing= new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(Define::loadAnim("Monster/Boss/wing.xml", "turnoff"),0.3)));
	normal_wing = new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(Define::loadAnim("Monster/Boss/wing.xml", "normal"), 0.06f)));
	turn_on_wing = new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(Define::loadAnim("Monster/Boss/wing.xml", "turnon"),0.3f)));
	wing->runAction(RepeatForever::create(normal_wing->get()));
	
	back->runAction(RepeatForever::create(back_anim->get()));
	face->runAction(RepeatForever::create(normal_face->get()));
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
		Flip(false);

	/*	face->getPhysicsBody()->setContactTestBitmask(0);
		face->getPhysicsBody()->setCollisionBitmask(0);*/
		wing->runAction(turn_on_wing->get());
		wing->runAction(MoveBy::create(0.5, Vec2(0, 50)));
		wing->runAction(RepeatForever::create(normal_wing->get()));
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

void BossPlane::Angry()
{
	//face->runAction(Sequence::create(angry_face->get(), DelayTime::create(1), normal_face->get()));
	face->runAction(angry_face->get());
}

void BossPlane::Break()
{
	ActiveWing(true);

	
	auto action = Sequence::create(MoveBy::create(1, Vec2(0, 200)),DelayTime::create(1), MoveBy::create(3, Vec2(-1000, 500)),nullptr);
	this->runAction(action);

}

void BossPlane::Fire()
{
	//auto missle1 = Sprite::create("Monster/Boss/missle.png",Rect(7,3,109,44));
	//auto missle2 = Sprite::create("Monster/Boss/missle.png", Rect(7, 3, 109, 44));
	//auto missle3= Sprite::create("Monster/Boss/missle.png", Rect(7, 3, 109, 44));
	Animate* missle = Animate::create(Animation::createWithSpriteFrames(Define::loadAnim("Monster/Boss/missle.xml", "1"), 0.05));
	for (int i = 0; i < 3; i++)
	{
		auto missle1 = Sprite::create("Monster/Boss/missle.png", Rect(7, 3, 109, 44));
		missle1->setFlipX(true);
		missle1->runAction(RepeatForever::create(missle->clone()));
		missle1->setTag(Define::MISSLE);
		missle1->setAnchorPoint(Vec2(0.5, 0.5));

		missle1->setRotation(-65);

		auto phy1 = PhysicsBody::createBox(Size(75, 25));
		phy1->setCategoryBitmask(8);
		phy1->setContactTestBitmask(3);
		phy1->setCollisionBitmask(0);
		phy1->setDynamic(false);

		missle1->setPhysicsBody(phy1);

		

	
		auto func = CallFunc::create([this]()
		{
			auto particle = ParticleSystemQuad::create("Particle/explosion.plist");
			particle->setPosition(this->getPosition());

			this->getParent()->addChild(particle);
		});
		auto node = this->getParent();

		auto createBoom = CallFunc::create([=]()
		{
			MyParticle::CreateBoom(missle1->getPosition(), node);
		});

		if (i == 0)
		{
			missle1->setPosition(this->getPosition() + Vec2(50, -20));
			missle1->runAction(Sequence::create(func,MoveBy::create(0.6, Vec2(-270, -700)),createBoom,RemoveSelf::create(), nullptr));
		
		}
		else if (i == 1) 
		{
			missle1->setPosition(this->getPosition() + Vec2(100, 20)); 
			//particle->setPosition(this->getPosition() + Vec2(100, 20));
			missle1->runAction(Sequence::create(DelayTime::create(0.3),func,MoveBy::create(0.8, Vec2(-270, -700)), createBoom, RemoveSelf::create(),nullptr));
		}
		else
		{
			auto back = CallFunc::create([this]()
			{
				auto boss_temp = (BossLv1*)boss;
				boss_temp->ReturnPlane();
			});
			missle1->setPosition(this->getPosition() + Vec2(150, -20));
			//particle->setPosition(this->getPosition() + Vec2(150, -20));
			missle1->runAction(Sequence::create(DelayTime::create(0.5), func, MoveBy::create(0.8, Vec2(-270, -700)), createBoom, back, RemoveSelf::create(), nullptr));
		}
		this->getParent()->addChild(missle1, 6);
		
		
	}
	
}

void BossPlane::Flip(bool isFlip)
{

	if (isFlip)
	{
		back->setAnchorPoint(Vec2(1, 1));
		back->setPosition(back->getPosition() + Vec2(back->getContentSize().width,0));
	/*	front->setPosition(front->getPosition() + Vec2(front->getContentSize().width+20, 0));
		wing->setPosition(wing->getPosition() + Vec2(wing->getContentSize().width-30, 0));
		face->setPosition(face->getPosition() + Vec2(face->getContentSize().width-65, 0));*/

	}
	else
	{
		back->setAnchorPoint(Vec2(0, 1));
		back->setPosition(0,0);
	}

	face->setFlipX(isFlip);
	back->setFlipX(isFlip);
	front->setFlipX(isFlip);
}
