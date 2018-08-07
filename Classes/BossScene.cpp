#include "BossScene.h"


BossScene::BossScene()
{
}


BossScene::~BossScene()
{
}

bool BossScene::init()
{
	LevelScene::init();

	_mSonic->setPosition(Vec2(900, 200));
    boss = new BossLv1(Vec2(1500, 317), _mSonic, (Layer*)this);
	//boss->Flip();
	this->addChild(boss);
	boss->SetState(BossLv1::IDLE);

	blacklayer = LayerColor::create(Color4B::BLACK);
	blacklayer->setScale(3);
	blacklayer->setOpacity(100);

	_mSonic->setZOrder(5);
	this->addChild(blacklayer,3);



	_mSonic->isFightingBoss = true;
	_mSonic->position_when_FightingBoss = _mSonic->getPosition();



	test = ParticleSystemQuad::create("Particle/charge.plist");

	test->setPosition(_mSonic->getPosition());
	this->addChild(test,4);
	








	CreateParallaxNode("Map_stone/stone_bg3.png");
	
	_tileMap = new TMXTiledMap();
	_tileMap->initWithTMXFile("LevelScene/StoneMap/boss.tmx");
	this->addChild(_tileMap);




	TMXObjectGroup *objectGroup_land = _tileMap->getObjectGroup("Land");
	for (int i = 0; i < objectGroup_land->getObjects().size(); i++)
	{

		Value objectemp = objectGroup_land->getObjects().at(i);

		float wi_box = objectemp.asValueMap().at("width").asFloat();
		float he_box = objectemp.asValueMap().at("height").asFloat();
		float x_box = objectemp.asValueMap().at("x").asFloat() + wi_box / 2;
		float y_box = objectemp.asValueMap().at("y").asFloat() + he_box / 2;

		auto edgeSp = Sprite::create();
		edgeSp->setTag(Define::land);


		auto boundBody = PhysicsBody::createBox(Size(wi_box, he_box), PhysicsMaterial(0.1f, 1.0f, 0.0f));
		boundBody->setDynamic(false);


		boundBody->setCategoryBitmask(2);
		boundBody->setCollisionBitmask(25);
		boundBody->setContactTestBitmask(1);

		edgeSp->setPhysicsBody(boundBody);
		edgeSp->setPosition(Vec2(x_box, y_box));

		this->addChild(edgeSp); // Add v�o Layer
	}

	experimental::AudioEngine::stopAll();
	Define::_music_boss_scene_background = experimental::AudioEngine::play2d(Define::_music_boss_scene_background_path, true, 0.8f);

	scheduleOnce(CC_SCHEDULE_SELECTOR(BossScene::updateStart), 0);
	return true;
}

cocos2d::Scene * BossScene::createScene()
{
	auto scene = Scene::createWithPhysics();

	// set gravity
	scene->getPhysicsWorld()->setGravity(Vec2(0, -1000));

	// optional: set debug draw
	//scene->getPhysicsWorld()->setDebugDrawMask(0xffff);
	scene->getPhysicsWorld()->step(1 / 60.0f);



	auto layer = BossScene::create();
	scene->addChild(layer);

	return scene;
}

void BossScene::update(float)
{
	if (_mSonic->mCurrentState->GetState() == SonicState::CHAOS)
	{
		test->setVisible(true);
		blacklayer->setVisible(true);
		if (test != nullptr)
			test->setPosition(_mSonic->getPosition());
		if (blacklayer != nullptr)
			blacklayer->setPosition(_mSonic->getPosition() + Vec2(-500, 0));
	}
	else
	{
		test->setVisible(false);
		blacklayer->setVisible(false);
	}
	if (boss->isCrazy)
	{
		//test->setVisible(tru);
		blacklayer->setVisible(true);
	}
	RollBackground();
	if (_mSonic->scene_over)
		return;

	if (_mSonic->getPosition().x < 0) _mSonic->setPosition(0, _mSonic->getPosition().y);
	if (boss->currentState == BossLv1::RUNBACK && boss->drill->getPositionX()<_mSonic->getPositionX())
	{
		SetViewPointCenter(_mSonic->getPosition(),Vec2(100,0) );
	}
	else 	SetViewPointCenter(_mSonic->getPosition(), Vec2(-200, 0));


}

void BossScene::updateStart(float dt)
{
	LevelScene::updateStart(1);
	_myui->current_scene = this;


	auto _progressbar = Sprite::create("GameComponents/progressbar2.png");
	_progressbar->setAnchorPoint(Vec2(0.5, 0.5));


	auto _border = Sprite::create("GameComponents/border2.png");

	_border->setAnchorPoint(Vec2(0.5, 0.5));
	_border->setPosition(_border->getContentSize()/2);
	this->getScene()->addChild(_border,0);


	mouseBar = ProgressTimer::create(_progressbar);
	mouseBar->setType(ProgressTimerType::RADIAL);
	mouseBar->setAnchorPoint(Vec2(0.5, 0.5));
	//	mouseBar->setReverseDirection(true);
	mouseBar->setPercentage(60);


	mouseBar->setPosition(_border->getContentSize()/2);
	boss->mouseBar = mouseBar;
//	mouseBar->setColor(Color3B::WHITE);
	this->getScene()->addChild(mouseBar,2);

	boss_avatar = Sprite::create();
	boss_avatar->setAnchorPoint(Vec2(0, 0));
	boss_avatar->setPosition(10, _border->getContentSize().height/2-30);
	this->getScene()->addChild(boss_avatar,1);
	
	normal_anim = new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(Define::loadAnim("Monster/Boss/boss_face.xml", "angry_avatar"), 0.05)));
	angry_anim= new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(Define::loadAnim("Monster/Boss/boss_face.xml", "normal_avatar"), 0.05)));
	boss_avatar->runAction(RepeatForever::create(normal_anim->get()));
}
void BossScene::ReloadScene()
{
	Director::getInstance()->replaceScene(this->createScene());
}