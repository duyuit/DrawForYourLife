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

	static void CreateWind(Vec2 pos, Layer* layer)
	{
		
		
		for (int i = 0; i < 10; i++)
		{
			int ran = RandomHelper::random_int(1, 3);
			Sprite* wind;
			switch (ran)
			{case 1:
				wind = Sprite::create("Particle/wind.png", Rect(0, 0, 207, 9));
				break;
			case 2:wind = Sprite::create("Particle/wind.png", Rect(0, 20, 342, 17));
				break;
			case 3: wind = Sprite::create("Particle/wind.png", Rect(0, 56, 194, 8));
				break;

			default:
				break;
			}
			wind->setOpacity(200);
			wind->setAnchorPoint(Vec2(0, 0));
			int ran2 = RandomHelper::random_int(1, 10);
			wind->setPosition(pos+ Vec2(1500+ 100 * ran +100 *ran2,100*ran + 50*ran2));
			wind->runAction(Sequence::create(MoveBy::create(1, Vec2(-2000, 0)), RemoveSelf::create(), nullptr));
			layer->addChild(wind);
		}


		
	};

}