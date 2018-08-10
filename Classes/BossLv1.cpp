#include "BossLv1.h"

#include "BossScene.h"
void BossLv1::GenerateButton()
{

		
		currentButton = new TapButton(Vec2(_mSonic->getPosition().x + 300, 350), _mSonic, (Layer*)this->getParent());
		currentButton->time = 0.8;
		currentButton->SetCanActive(true);
		currentButton->_action = SonicState::ROLL_IN_SKY;
		currentButton->setZOrder(5);

}

void BossLv1::GenerateMultiButton()
{

	current_multiButton = new MultipleButton(Vec2(_mSonic->getPosition().x + 300, 350), _mSonic, (Layer*)this->getParent(), 3, 2.5, 0);
	current_multiButton->_action = SonicState::ROLL_IN_SKY;
	current_multiButton->canActive = true;
	current_multiButton->setZOrder(5);

}

BossLv1::BossLv1(Vec2 pos , Sonic* sonic, Layer* layer)
{
	drill = new BossDrill();
	drill->parent = this;

	plane = new BossPlane();
	plane->boss = this;
	drill->setPosition(pos);
	_mSonic = sonic;

	auto active_car = CallFunc::create([this]()
	{
		drill->ActiveDrill();
		plane->ActiveWing(false);
	});
	plane->setPosition(pos+Vec2(500,500));


	
	plane->runAction(Sequence::create(
		MoveTo::create(2, pos+Vec2(110,50 + 300)),
		DelayTime::create(0.4),
		MoveBy::create(2,Vec2(0,-300)),
		DelayTime::create(0.3),
		active_car,
		nullptr));



	this->scheduleUpdate();
	layer->addChild(drill,6);
	layer->addChild(plane,5);
	this->setPosition(pos);
	_mSonic->boss = this;



	


	
}


BossLv1::~BossLv1()
{
}

void BossLv1::GetDame()
{
	if (isDelete) return;
	hp--;
	auto particle = ParticleSystemQuad::create("Particle/explosion.plist");
	particle->setPosition(plane->getPosition());
	plane->getParent()->addChild(particle, 4);
	//Define::_boss_hurt_effect = experimental::AudioEngine::play2d(Define::_boss_hurt_effect_path, false, 1.0f);

	if (hp < 5)
		isAlmostBroke = true;
	if (hp == 0)
	{
		Broke();
		return;
	}
	/*auto action = TintTo::create(0.2, Color3B::WHITE);
	auto action2= TintTo::create(0.2, Color3B(255,255,255));
	drill->runAction(Blink::create(1,5));
	plane->runAction(Blink::create(1,5));*/
	plane->Angry();
	//drill->runAction(action);
}



void BossLv1::ResetButton()
{
	currentButton->DeleteNow(true);
	currentButton = nullptr;
}

void BossLv1::Broke()
{
	isDelete = true;
	drill->Break();
	drill->stopAllActions();
	plane->stopAllActions();
	plane->Break();
}

void BossLv1::ReturnPlane()
{
	//plane->stopAllActions();
	auto func = CallFunc::create([this]()
	{
		isCrazy = false;
		this->SetState(FIGHT);
	});
	plane->runAction(Sequence::create(MoveTo::create(2, drill->getPosition() + Vec2(110, 50)),func,NULL));
	plane->ActiveWing(false);

}

void BossLv1::AddPercent(TYPE_SCORE score)
{

	float per = mouseBar->getPercentage();
	switch (score)
	{
	case PERFECT:
		if (per + 40 >= 100)
		{
			experimental::AudioEngine::play2d(Define::_music_alert_effect_path, false, 1.0f);
			mouseBar->runAction(ProgressFromTo::create(0.5, per, 100));
			isCrazy = true;
		}
		else 	mouseBar->runAction(ProgressFromTo::create(0.5, per, per +40));

		break;
	case GREAT:
		if (per + 25 >= 100)
		{
			experimental::AudioEngine::play2d(Define::_music_alert_effect_path, false, 0.8f);
			mouseBar->runAction(ProgressFromTo::create(0.5, per, 100));
			isCrazy = true;
		}
		else 	mouseBar->runAction(ProgressFromTo::create(0.5, per, per + 25));
		break;
	default:
		break;
	}
}

void BossLv1::SetState(STATE state)
{
	if (isDelete) return;
	count_to_change_state = 0;
	switch (state)
	{
	case BossLv1::IDLE:
		drill->chain1->getPhysicsBody()->setCollisionBitmask(0);
		break;
	case BossLv1::RUN:
	{	
		

		drill->chain1->setVisible(false);
		drill->chain2->setVisible(false);
		drill->chain3->setVisible(false);
		drill->chain1->getPhysicsBody()->setContactTestBitmask(0);
		drill->chain1->getPhysicsBody()->setCollisionBitmask(0);

		if (isCrazy)
		{
			GenerateMultiButton();

			/*drill->runAction(Sequence::create(JumpBy::create(2, Vec2(-500, 500),300,1 ),
				JumpBy::create(0.2, Vec2(-100,-500), 0, 1),
				MoveBy::create(0.1, Vec2(0, -15)),
				MoveBy::create(0.1, Vec2(0, 15)),
				MoveBy::create(0.05, Vec2(0, 10)),
				MoveBy::create(0.05, Vec2(0, -10)),
				MoveBy::create(0.05, Vec2(0, 5)),
				MoveBy::create(0.05, Vec2(0, -5)),
					nullptr));*/
			plane->ActiveWing(true);
			auto fire = CallFunc::create([this]()
			{
				plane->Fire();
			});
			plane->runAction(Sequence::create(JumpBy::create(2, Vec2(-500, 500), 300, 1),
				MoveBy::create(0.1, Vec2(0, -15)),
				MoveBy::create(0.1, Vec2(0, 15)),
				MoveBy::create(0.05, Vec2(0, 10)),
				MoveBy::create(0.05, Vec2(0, -10)),
				MoveBy::create(0.05, Vec2(0, 5)),
				MoveBy::create(0.05, Vec2(0, -5)),
				fire,
				nullptr));
			

			auto jet1 = Sprite::create();
			auto jet2 = Sprite::create();
			auto jet_anim = Animate::create(Animation::createWithSpriteFrames(Define::loadAnim("Particle/boss_jet.xml", "1"), 0.03));
		
			jet1->runAction(RepeatForever::create(jet_anim->clone()));
			jet2->runAction(RepeatForever::create(jet_anim->clone()));
			jet1->runAction(Sequence::create(DelayTime::create(0.5), RemoveSelf::create(), nullptr));
			jet2->runAction(Sequence::create(DelayTime::create(0.5), RemoveSelf::create(), nullptr));

			jet1->setPosition(drill->getPosition() + Vec2(0, -100));
			jet2->setPosition(drill->getPosition() + Vec2(200, -100));

			drill->getParent()->addChild(jet1);
			drill->getParent()->addChild(jet2);
		}
		else
		{
			GenerateButton();
			auto flip = CallFunc::create([this]() {
				drill->Flip(true);
				plane->Flip(true);
			});

			drill->runAction(Sequence::create(
				MoveBy::create(4, Vec2(-1500, 0)),
				flip,
				NULL));
			plane->runAction(Sequence::create(
				MoveBy::create(4, Vec2(-1500, 0)),
				NULL));
		}
	
	}
		break;
	case BossLv1::RUNBACK:
	{	
		if (isCrazy && drill->getPositionX() > _mSonic->getPositionX())
		{
		ReturnPlane();
		isCrazy = false;
		}
		else
		{
			GenerateButton();

			auto flip2 = CallFunc::create([this]() {
				drill->Flip(true);
				plane->Flip(true);
			});

			auto flip = CallFunc::create([this]() {
				drill->Flip(false);
				plane->Flip(false);
			});

			drill->runAction(Sequence::create(
				MoveBy::create(5, Vec2(1800, 0)),
				flip,
				MoveBy::create(1, Vec2(-300, 0)),
				NULL));
			plane->runAction(Sequence::create(
				MoveBy::create(5, Vec2(1800, 0)),
				MoveBy::create(1, Vec2(-300, 0)),
				NULL));
		}
	
		
	}
		break;

	case BossLv1::FIGHT:
		drill->chain1->setVisible(true);
		drill->chain2->setVisible(true);
		drill->chain3->setVisible(true);
		drill->chain1->getPhysicsBody()->setCollisionBitmask(1);
		drill->chain1->getPhysicsBody()->setContactTestBitmask(1);
		
		if (isCrazy)
		{

			GenerateMultiButton();
			drill->drill->stopAllActions();
			drill->drill->runAction(RepeatForever::create(drill->drill_crazy_anim->get()));
			auto func = CallFunc::create([this]()
			{
				drill->FireDrillCrazy();
				Define::_music_drill_attack_effect = experimental::AudioEngine::play2d(Define::_music_drill_attack_effect_path, false, 1.0f);
			});
			drill->runAction(Sequence::create(DelayTime::create(1.8), func, nullptr));
	
		}else
		{	
			
			GenerateButton();
			drill->FireDrill(); 
			Define::_music_drill_attack_effect = experimental::AudioEngine::play2d(Define::_music_drill_attack_effect_path, false, 1.0f);
		}
		break;	
	case BossLv1::GETBACKDRILL:
		{
	//	delete currentButton;
		drill->drill->stopAllActions();
		drill->drill->runAction(RepeatForever::create(drill->drill_anim->get()));
		if(!isSonicAttack)
		GenerateButton();
	}
		
		break;
	default:
		break;
	}
	currentState = state;
}

void BossLv1::update(float dt)
{
	if (isDelete) return;
	if (_mSonic->mCurrentState->GetState() == SonicState::CHAOS && _mSonic->CheckLastFrame() && isSonicAttack)
	{
		auto func = CallFunc::create([this]()
		{
			GetDame();
			MyParticle::CreateBoom(_mSonic->getPosition(), _mSonic->getParent());
			_mSonic->SetStateByTag(SonicState::FALL);
			_mSonic->getPhysicsBody()->applyImpulse(Vec2(-300000, 150000));
			experimental::AudioEngine::stop(_music_chao_id);
			experimental::AudioEngine::play2d(Define::_music_sonic_chao_attack_effect_path, false, 0.8f);
		});
		_mSonic->runAction(Sequence::create(MoveTo::create(0.3, plane->getPosition()),func,nullptr));
		isSonicAttack = false;
	}
	if (current_multiButton != nullptr)
		{
			float currentDrillPosition = drill->getPositionX() + drill->drill->getPositionX();

			if (currentState == FIGHT)
			{
				if (current_multiButton->isTrue)
				{
					mouseBar->runAction(ProgressTo::create(1, 0));
					_mSonic->SetStateByTag(SonicState::CHAOS);
					isCrazy = false;
					_mSonic->getPhysicsBody()->applyImpulse(Vec2(150000, 300000));
					_mSonic->isLeft = true;
					isSonicAttack = true;
					current_multiButton->DeleteNow(true);
					current_multiButton = nullptr;

					_music_chao_id = experimental::AudioEngine::play2d(Define::_music_sonic_chao_effect_path, false, 1.5f);
				}
				else
				{
					if (current_multiButton->isDelete)
					{
						mouseBar->runAction(ProgressTo::create(1, 0));
						isCrazy = false;
						current_multiButton = nullptr;
					}
				}

			}
			else if (currentState == RUN)
			{
				if (current_multiButton->isTrue)
				{
					_mSonic->SetStateByTag(SonicState::RUNSKIP);
					mouseBar->runAction(ProgressTo::create(1, 0));
					auto func = CallFunc::create([this]()
					{
						_mSonic->_roll_effect->setRotation(-90);
						_mSonic->_roll_effect->setPosition(_mSonic->_roll_effect->getPosition() + Vec2(-100, 50));
						_mSonic->SetStateByTag(SonicState::ROLL_CHEST);
						_mSonic->getPhysicsBody()->applyImpulse(Vec2(0, 500000));
					});
					_mSonic->runAction(Sequence::create(MoveBy::create(0.5, Vec2(0, 0)), func, NULL));
					current_multiButton = nullptr;
				}
				else
				{
					if (current_multiButton->isDelete)
					{
						mouseBar->runAction(ProgressTo::create(1, 0));
						isCrazy = false;
						current_multiButton = nullptr;
					}
				}
			
			}

		}
	
	if (currentButton != nullptr)
	{
		
		currentButton->setPosition(_mSonic->getPosition().x+300,350);

		float currentDrillPosition = drill->getPositionX() + drill->drill->getPositionX();

		if (currentState == FIGHT)
		{
			if (currentDrillPosition - _mSonic->getPositionX() < 50
				&& currentButton->isTrue
				&&_mSonic->mCurrentState->GetState() != SonicState::ROLL_IN_SKY)
			{

				_mSonic->SetStateByTag(SonicState::ROLL_IN_SKY);
				_mSonic->getPhysicsBody()->applyForce(Vec2(0, 15500000));
				_mSonic->isLeft = true;
				AddPercent(currentButton->score);
				ResetButton();

				//GenerateButton();
			}else
				if (currentButton->isTrue	&&_mSonic->mCurrentState->GetState() == SonicState::ROLL_IN_SKY)
				{
			
					_mSonic->SetStateByTag(SonicState::ROLL_IN_SKY);

				//	isSonicAttack = true;
					_mSonic->getPhysicsBody()->applyForce(Vec2(0, 15500000));
					AddPercent(currentButton->score);
					ResetButton();
				}
			
		}
		else if (currentState == GETBACKDRILL)
		{
			if (_mSonic->getPositionX() - currentDrillPosition < 600
				&& currentButton->isTrue
				&& _mSonic->mCurrentState->GetState() != SonicState::ROLL_IN_SKY)
			{

				_mSonic->SetStateByTag(SonicState::ROLL_IN_SKY);
				_mSonic->getPhysicsBody()->applyForce(Vec2(0, 15500000));
				_mSonic->isLeft = false;
			
				AddPercent(currentButton->score);
				ResetButton();

			}
		}
		else if (currentState == RUN)
		{
				if (currentDrillPosition - _mSonic->getPositionX() < 300
					&& currentButton->isTrue
					&& _mSonic->mCurrentState->GetState() != SonicState::ROLL_IN_SKY)
				{
						_mSonic->SetStateByTag(SonicState::ROLL_IN_SKY);
						_mSonic->getPhysicsBody()->applyForce(Vec2(0, 20500000));
						//_mSonic->getPhysicsBody()->applyImpulse(Vec2(0, 100000));
						_mSonic->isLeft = true;
					
						AddPercent(currentButton->score);
						ResetButton();
			
						maximum_hit = 1;
				}else
				if (_mSonic->mCurrentState->GetState() == SonicState::ROLL_IN_SKY && currentButton->isTrue)
				{
					
						_mSonic->runAction(MoveTo::create(0.3, plane->getPosition()));
						
						AddPercent(currentButton->score);
						ResetButton();
		
					
				}
				
		}
		else if (currentState == RUNBACK)
		{
			if (_mSonic->getPositionX() - currentDrillPosition < 400
				&& currentButton->isTrue
				&& _mSonic->mCurrentState->GetState() != SonicState::ROLL_IN_SKY)
			{
				_mSonic->SetStateByTag(SonicState::ROLL_IN_SKY);
				_mSonic->getPhysicsBody()->applyForce(Vec2(0, 20500000));
				_mSonic->isLeft = true;
			
				AddPercent(currentButton->score);
				ResetButton();
				maximum_hit = 1;
			
			}
			else 
			if (_mSonic->mCurrentState->GetState() == SonicState::ROLL_IN_SKY && currentButton->isTrue)
			{
				_mSonic->runAction(MoveTo::create(0.5, plane->getPosition()+Vec2(300,0)));
			
				AddPercent(currentButton->score);
				ResetButton();

			}
		}
	}

	if (_mSonic->mCurrentState->GetState() == SonicState::IDLE || _mSonic->mCurrentState->GetState() == SonicState::CHAOS)
	{
		if (drill->getPositionX() < _mSonic->getPositionX())
			_mSonic->isLeft = true;
		else _mSonic->isLeft = false;
	}
	count_to_change_state++;
	switch (currentState)
	{
	case BossLv1::RUNBACK:
			if (count_to_change_state == 60 *6)
			{

				SetState(FIGHT);
			}
	
	
		break;
	case BossLv1::IDLE:
		if (count_to_change_state == 60*5)
		{
		
			SetState(RUN);
		}
		break;
	case BossLv1::RUN:
		if (count_to_change_state == 60 *6)
		{
		
			SetState(RUNBACK);
		}
		break;
	case BossLv1::FIGHT:
	
		break;
	case BossLv1::GETBACKDRILL:
		
		if (count_to_change_state == 60 *3)
		{
			count_to_change_state = 0;
			SetState(RUN);
		}
		break;
	default:
		break;
	}

	if (count_to_change_state % 20 == 0 && isAlmostBroke)
		drill->AlmostBreak();


	//if (count_to_change_state == 60*6)
	//{
	////	count_to_change_state = 0;
	//	SetState(RUN);
	//}
}

void BossLv1::Merge()
{
}

void BossLv1::Flip()
{
	//drill->Flip();

}
