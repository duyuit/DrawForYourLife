#pragma once
#include "GameDefine.h"
namespace MyParticle
{
	static void CreateEatItem(Vec2 pos, Layer* layer)
	{
		Vector<SpriteFrame*> dualSmokeFrameList = Define::loadAnim("Particle/particle.xml", "eat_item");
		RefPtr<Animate> *dualSmoke = new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(dualSmokeFrameList, 0.08f)));
		Sprite *smoke = Sprite::create();
		smoke->setScale(1.5, 1.5);
		smoke->setAnchorPoint(Vec2(0.5, 0.5));
		smoke->setPosition(pos);
		layer->addChild(smoke);

		auto sequence = Sequence::create(dualSmoke->get(), RemoveSelf::create(), NULL);
		smoke->runAction(sequence);
	};
	static void CreateLandSmoke(Vec2 pos, Layer* layer)
	{
		Vector<SpriteFrame*> dualSmokeFrameList = Define::loadAnim("Particle/particle.xml", "land_smoke");
		RefPtr<Animate> *dualSmoke = new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(dualSmokeFrameList, 0.08f)));
		Sprite *smoke = Sprite::create();
		smoke->setScale(2);
		smoke->setAnchorPoint(Vec2(0.5, 0));
		smoke->setPosition(pos);
		layer->addChild(smoke);

		auto sequence = Sequence::create(dualSmoke->get(), RemoveSelf::create(), NULL);
		smoke->runAction(sequence);
	};
	static void CreateFlyingSmoke(Vec2 pos, Layer* layer)
	{
		Vector<SpriteFrame*> dualSmokeFrameList = Define::loadAnim("Particle/particle.xml", "flying_smoke");
		RefPtr<Animate> *dualSmoke = new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(dualSmokeFrameList, 0.08f)));
		Sprite *smoke = Sprite::create();
		smoke->setScale(1.5, 1.5);
		smoke->setAnchorPoint(Vec2(0.5, 0.5));
		smoke->setPosition(pos);
		layer->addChild(smoke);

		auto sequence = Sequence::create(dualSmoke->get(), RemoveSelf::create(), NULL);
		smoke->runAction(sequence);
	};


}