#include "FrogMonster.h"

using namespace Define;

FrogMonster::FrogMonster(Sonic* sonic)
{
	//Bug Android. Clang version
//	Monster::Monster(sonic);
	Vector<SpriteFrame*> runFL = loadAnim("Monster/frog.xml", "run");
	Vector<SpriteFrame*> dieFL = loadAnim("Monster/frog.xml", "die");
	Vector<SpriteFrame*> idleFL = loadAnim("Monster/frog.xml", "idle");
	Vector<SpriteFrame*> fightFL = loadAnim("Monster/frog.xml", "fight");

	_runAni = new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(runFL, 0.07f)));
	_dieAni = new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(dieFL, 0.2f)));
	_idleAni = new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(idleFL, 0.1f)));
	_fightAni = new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(fightFL, 0.05f)));

	Monster::Init(sonic);
	this->setScale(0.8);

	_multiButton = new MultipleButton(Vec2(0, 0), _mSonic, (Layer*)_mSonic->getParent(), 2, 2, 0);

	//this->init();
	//this->initWithSpriteFrame(idleFL.at(0));
	//auto verti = PhysicsBody::createBox(this->getContentSize(), PhysicsMaterial(0.1f, 0.0f, 0.0f));

	//verti->setCategoryBitmask(16);    // 0010
	//verti->setCollisionBitmask(2);   // 0001
	//verti->setContactTestBitmask(1);

	//verti->setRotationEnable(false);
	//verti->setDynamic(true);
	//this->setPhysicsBody(verti);
	//this->setTag(LANDMONSTER);

	//_mSonic = sonic;
	//_tapButton = new TapButton(RandomHelper::random_int(1, 4), Vec2(0, 0), _mSonic, (Layer*)_mSonic->getParent());
	//_tapButton->isFirst = true;
	//_tapButton->_action = SonicState::ROLL;
	////_tapButton->unscheduleUpdate();


	//this->setAnchorPoint(Vec2(0.5f, 0));
	//SetStateByTag(IDLE);
	//this->scheduleUpdate();

}


FrogMonster::~FrogMonster()
{
}

//void FrogMonster::HandleCollision(Sprite * sprite)
//{
//}
//
//void FrogMonster::update(float dt)
//{
//}
//
//void FrogMonster::SetStateByTag(MONSTERSTATE state)
//{
//}
