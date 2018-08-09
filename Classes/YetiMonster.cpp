#include "YetiMonster.h"
using namespace Define;

YetiMonster::YetiMonster(Sonic* sonic)
{
	//Bug Android. Clang version
	//	Monster::Monster(sonic);
	Vector<SpriteFrame*> runFL = loadAnim("Monster/yeti_monster.xml", "run");
	Vector<SpriteFrame*> dieFL = loadAnim("Monster/yeti_monster.xml", "die");
	Vector<SpriteFrame*> idleFL = loadAnim("Monster/yeti_monster.xml", "idle");
	Vector<SpriteFrame*> fightFL = loadAnim("Monster/yeti_monster.xml", "fight");

	_runAni = new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(runFL, 0.07f)));
	_dieAni = new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(dieFL, 0.2f)));
	_idleAni = new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(idleFL, 0.1f)));
	_fightAni = new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(fightFL, 0.05f)));

	Monster::Init(sonic);
	this->setScale(1);
	_multiButton = new MultipleButton(Vec2(0, 0), _mSonic, (Layer*)_mSonic->getParent(), 2, 2, 1);
}

YetiMonster::~YetiMonster()
{
}


