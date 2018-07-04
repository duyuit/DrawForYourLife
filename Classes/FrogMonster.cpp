#include "FrogMonster.h"

using namespace Define;

FrogMonster::FrogMonster()
{
	
	Monster::Monster();
	Vector<SpriteFrame*> runFL = loadAnim("Monster/frog.xml", "run");
	Vector<SpriteFrame*> dieFL = loadAnim("Monster/frog.xml", "die");
	Vector<SpriteFrame*> idleFL = loadAnim("Monster/frog.xml", "idle");
	Vector<SpriteFrame*> fightFL = loadAnim("Monster/frog.xml", "fight");

	_runAni = new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(runFL, 0.07f)));
	_dieAni = new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(dieFL, 0.2f)));
	_idleAni = new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(idleFL, 0.1f)));
	_fightAni = new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(fightFL, 0.05f)));

	

}


FrogMonster::~FrogMonster()
{
}
