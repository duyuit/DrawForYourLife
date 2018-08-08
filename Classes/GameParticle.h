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
	static void CreateHit(Vec2 pos, Node* node)
	{
		auto boom = Sprite::create();
		boom->setScale(1.5);
		boom->setAnchorPoint(Vec2(0.5, 0.5));
		boom->setPosition(pos);
		auto animate = Animate::create(Animation::createWithSpriteFrames(Define::loadAnim("Particle/particle.xml", "hit"), 0.05));
		boom->runAction(animate);
		boom->runAction(Sequence::create(DelayTime::create(0.3), RemoveSelf::create(), NULL));
		node->addChild(boom, 10);
	}
	static void CreateBoom(Vec2 pos, Node* node)
	{
		auto boom = Sprite::create();
		boom->setScale(1.5);
		boom->setAnchorPoint(Vec2(0.5, 0.5));
		boom->setPosition(pos);
		auto animate= Animate::create(Animation::createWithSpriteFrames(Define::loadAnim("Particle/particle.xml", "boom"), 0.05));
		boom->runAction(animate->clone());
		boom->runAction(Sequence::create(DelayTime::create(0.3), RemoveSelf::create(), NULL));
		node->addChild(boom,10);
	}
	static void CreateCarSmoke(Vec2 pos, Node* node)
	{
		auto dust = Sprite::create();
		int a = RandomHelper::random_int(1, 2);
		Animate* anim;
		if (a == 1)
			anim = Animate::create(Animation::createWithSpriteFrames(Define::loadAnim("Particle/particle.xml", "dust1"), 0.05));
		else
			anim = Animate::create(Animation::createWithSpriteFrames(Define::loadAnim("Particle/particle.xml", "dust2"), 0.05));
		dust->runAction(anim);
		dust->runAction(Sequence::create(DelayTime::create(0.3), RemoveSelf::create(), NULL));
		dust->setPosition(pos);
		node->addChild(dust);
	}
	static void CreateElectric(Vec2 pos, Node* node)
	{
		auto ele = Sprite::create();
		ele->setPosition(pos);
		ele->runAction(Animate::create(Animation::createWithSpriteFrames(Define::loadAnim("Particle/particle.xml", "electric"), 0.05)));
		ele->runAction(Sequence::create(DelayTime::create(0.3), RemoveSelf::create(), nullptr));
		node->addChild(ele,5);
	}
	static void RunEffectStar(Vec2 pos, Layer* layer) {
		/*ccBezierConfig  bezier5;
		ccBezierConfig  bezier1;
		ccBezierConfig  bezier2;
		ccBezierConfig  bezier3;
		ccBezierConfig  bezier4;
		Sprite* bling1;
		Sprite* bling2;
		Sprite* bling3;
		Sprite* bling4;
		Sprite* bling5;
		bling1 = Sprite::create("Level_map/bling_green.png");
		bling2 = Sprite::create("Level_map/bling_pur.png");
		bling3 = Sprite::create("Level_map/bling_orange.png");
		bling4 = Sprite::create("Level_map/bling_blue.png");
		bling5 = Sprite::create("Level_map/bling_yellow.png");
		bling1->setAnchorPoint(Vec2(0.5f, 0));
		bling1->setVisible(false);
		bling1->setScale(3);
		layer->addChild(bling1, 2);

		bling2->setAnchorPoint(Vec2(0.5f, 0));
		bling2->setVisible(false);
		bling2->setScale(3);
		layer->addChild(bling2, 2);

		bling3->setAnchorPoint(Vec2(0.5f, 0));
		bling3->setVisible(false);
		bling3->setScale(3);
		layer->addChild(bling3, 2);

		bling4->setAnchorPoint(Vec2(0.5f, 0));
		bling4->setVisible(false);
		bling4->setScale(3);
		layer->addChild(bling4, 2);

		bling5->setAnchorPoint(Vec2(0.5f, 0));
		bling5->setVisible(false);
		bling5->setScale(3);
		layer->addChild(bling5, 2);

		auto x = pos.x;
		auto y = pos.y;
		bling1->setPosition(x+ 100, y);
		bezier1.controlPoint_1 = Point(x + 20, y+ 20);
		bezier1.controlPoint_2 = Point(x + 40, y + 40);
		bezier1.endPosition = Point(x + 60, y + 10);

		bling1->setPosition(x -50, y);
		bezier2.controlPoint_1 = Point(x- 20, y + 20);
		bezier2.controlPoint_2 = Point(x - 40, y + 40);
		bezier2.endPosition = Point(x - 60, y + 10);

		bling1->setPosition(x  , y);
		bezier3.controlPoint_1 = Point(x + 15, y + 60);
		bezier3.controlPoint_2 = Point(x+ 35, y + 80);
		bezier3.endPosition = Point(x + 55, y + 70);

		bling1->setPosition(x +25, y);

		bezier4.controlPoint_1 = Point(x + 10, y + 25);
		bezier4.controlPoint_2 = Point(x+ 30, y + 45);
		bezier4.endPosition = Point(x+ 50, y+ 15);

		bling1->setPosition(x - 25, y);
		bezier5.controlPoint_1 = Point(x- 10, y + 20);
		bezier5.controlPoint_2 = Point(x - 30, y + 40);
		bezier5.endPosition = Point(x- 50, y+ 10);

		auto action1 = BezierBy::create(0.5, bezier1);
		auto action2 = BezierBy::create(0.5, bezier2);
		auto action3 = BezierBy::create(0.5, bezier3);
		auto action4 = BezierBy::create(0.5, bezier4);
		auto action5 = BezierBy::create(0.5, bezier5);
		bling1->setVisible(true);
		bling2->setVisible(true);
		bling3->setVisible(true);
		bling4->setVisible(true);
		bling5->setVisible(true);
		bling1->runAction(Sequence::create(action1, DelayTime::create(0.2f), RemoveSelf::create(), NULL));
		bling2->runAction(Sequence::create(action2, DelayTime::create(0.2f), RemoveSelf::create(), NULL));
		bling3->runAction(Sequence::create(action3, DelayTime::create(0.2f), RemoveSelf::create(), NULL));
		bling4->runAction(Sequence::create(action4, DelayTime::create(0.2f), RemoveSelf::create(), NULL));
		bling5->runAction(Sequence::create(action5, DelayTime::create(0.2f), RemoveSelf::create(), NULL));

		if (stt = 1) {
		action1 = BezierBy::create(0.75, bezier1);
		action2 = BezierBy::create(0.75, bezier2);
		action3 = BezierBy::create(0.75, bezier3);
		bling1->setVisible(true);
		bling2->setVisible(true);
		bling3->setVisible(true);
		bling1->runAction(Sequence::create(action1, DelayTime::create(0.2f), RemoveSelf::create(), NULL));
		bling2->runAction(Sequence::create(action2, DelayTime::create(0.2f), RemoveSelf::create(), NULL));
		bling3->runAction(Sequence::create(action3, DelayTime::create(0.2f), RemoveSelf::create(), NULL));
		}
		//*/
		//			auto star_effect = Sprite::create();
		//			auto star_anim = new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(loadAnim("Level_map/star_ani.xml", "star_effect"), 0.5f)));
		//			star_effect->runAction(RepeatForever::create(star_anim->get()));
		//			star_effect->setScale(1.2);
		//			star_effect->setPosition(layer->getPosition() + Vec2(25, 0));
		//			star_effect->setVisible(false);
		//			layer->addChild(star_effect, 100);

		Vector<SpriteFrame*> star_effect = Define::loadAnim("Level_map/star_ani.xml", "star_effect");
		RefPtr<Animate> *star_anim = new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(star_effect, 0.07f)));
		Sprite *star = Sprite::create();
		star->setScale(1.2);
		star->setAnchorPoint(Vec2(0.5, 0.5));
		star->setPosition(pos.x, pos.y + 80);
		layer->addChild(star);

		auto sequence = Sequence::create(star_anim->get(), RemoveSelf::create(), NULL);
		star->runAction(sequence);
	}
}