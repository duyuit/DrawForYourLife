#include "FinishLayer.h"
#include "LevelScene.h"
#include "LevelMap.h"
Button* button_board_cancel;
Button* button_board_round;
//
Button* button_board_next;
//
FinishLayer::FinishLayer(Sonic* mSonic, Layer* cur_scene, SCENE_LEVELMAP currentLevelMap)
{
	this->autorelease();
	mySonic = mSonic;
	current_scene = cur_scene;
	levelMap = currentLevelMap;
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();	


	//Star Count Score
	countPerfect = mySonic->countPerfect;
	countGreat = mySonic->countGreat;
	countBad = mySonic->countBad;
	score = mySonic->score;
	maxCombo = mySonic->maxCombo;
	ring = mySonic->ringCollected;


	if (maxCombo < 10 && maxCombo >= 0) {
		bonus += maxCombo * 30;
	}
	if (maxCombo < 20 && maxCombo >= 10) {
		bonus += maxCombo * 60;
	}
	if (maxCombo < 30 && maxCombo >= 20) {
		bonus += maxCombo * 120;
	}
	if (maxCombo >= 30 && maxCombo >= 20) {
		bonus += maxCombo * 240;
	}


	//	if (countPerfect <= 10 && countPerfect >= 0) {
	//		bonus += countPerfect * 60;
	//	}
	//	if (countPerfect <= 20 && countPerfect >= 10) {
	//		bonus += countPerfect * 120;
	//	}
	//	if (countPerfect <= 30 && countPerfect >= 20) {
	//		bonus += countPerfect * 240;
	//	}
	//	if (countPerfect >= 30) {
	//		bonus += countPerfect * 480;
	//	}
	//
	//total = score + bonus;

	if (score >= 14000) {
		numStar = 3;
	}
	if (score >= 7000 && score < 14000) {
		numStar = 2;
	}
	if (score > 0 && score < 7000) {
		numStar = 1;
	}

	//////
	float scaleX = 0.7;
	float scaleY = 0.7;
	boardScore = Sprite::create("Finish_Layer/score_board.png");
	boardScore->setScale(scaleX, scaleY);
	boardScore->setPosition(visibleSize.width / 2, visibleSize.height * 4 / 2);
	boardScore->setAnchorPoint(Vec2(0.5f, 0.5f));
	this->addChild(boardScore, 20);

	_bar = Sprite::create("Finish_Layer/bar.png");
	_bar->setPosition(boardScore->getContentSize().width * 4 / 8, boardScore->getContentSize().height * 2.3 / 4);
	_bar->setAnchorPoint(Vec2(0.5f, 0.5f));
	_bar->setVisible(false);
	boardScore->addChild(_bar, 21);

	auto start_jump_point = CallFunc::create([this]()
	{
		isJumpPoint = true;
	});

	//boardScore->runAction(MoveTo::create(1.5f,Vec2(visibleSize.width / 2, visibleSize.height / 2)));
	boardScore->runAction(Sequence::create(MoveTo::create(1.0f, Vec2(visibleSize.width / 2, visibleSize.height / 2)), start_jump_point, nullptr));

	_result = Label::createWithTTF("FINISH RESULT", font, 70);
	_result->setColor(Color3B::WHITE);
	_result->enableOutline(Color4B::BLACK, 5);
	_result->setPosition(boardScore->getContentSize().width / 2, boardScore->getContentSize().height*4.5 / 4);
	boardScore->addChild(_result, 100);

	_labelRing = Label::createWithTTF("Ring", font, 50);
	_labelRing->setColor(Color3B::YELLOW);
	_labelRing->setPosition(boardScore->getContentSize().width / 8, boardScore->getContentSize().height*3.5 / 4);
	_labelRing->setAnchorPoint(Vec2(0, 0.5f));
	boardScore->addChild(_labelRing, 100);

	_labelRingNum = Label::createWithTTF("", font, 50);
	_labelRingNum->setColor(Color3B::YELLOW);
	_labelRingNum->setPosition(boardScore->getContentSize().width * 6 / 8, boardScore->getContentSize().height * 3.5 / 4);
	_labelRingNum->setAnchorPoint(Vec2(0, 0.5f));
	boardScore->addChild(_labelRingNum, 100);

	_labelPerfect = Label::createWithTTF("Perfect", font, 40);
	_labelPerfect->setColor(Color3B(255, 0, 128));
	_labelPerfect->setPosition(boardScore->getContentSize().width / 8, boardScore->getContentSize().height * 3 / 4);
	_labelPerfect->setAnchorPoint(Vec2(0, 0.5f));
	boardScore->addChild(_labelPerfect, 100);

	_labelPerfectNum = Label::createWithTTF("", font, 40);
	_labelPerfectNum->setColor(Color3B(255, 0, 128));
	_labelPerfectNum->setPosition(boardScore->getContentSize().width * 6 / 8, boardScore->getContentSize().height * 3 / 4);
	_labelPerfectNum->setAnchorPoint(Vec2(0, 0.5f));
	boardScore->addChild(_labelPerfectNum, 100);

	_labelBestcombo = Label::createWithTTF("Best Combo", font, 40);
	_labelBestcombo->setColor(Color3B::GREEN);
	_labelBestcombo->setPosition(boardScore->getContentSize().width / 8, boardScore->getContentSize().height * 2.5 / 4);
	_labelBestcombo->setAnchorPoint(Vec2(0, 0.5f));
	boardScore->addChild(_labelBestcombo, 100);

	_labelBestcomboNum = Label::createWithTTF("", font, 40);
	_labelBestcomboNum->setColor(Color3B::GREEN);
	_labelBestcomboNum->setPosition(boardScore->getContentSize().width * 6 / 8, boardScore->getContentSize().height * 2.5 / 4);
	_labelBestcomboNum->setAnchorPoint(Vec2(0, 0.5f));
	boardScore->addChild(_labelBestcomboNum, 100);

	//_labelBonus = Label::createWithTTF("Bonus", font, 40);
	//_labelBonus->setColor(Color3B::GREEN);
	//_labelBonus->setPosition(boardScore->getContentSize().width / 8, boardScore->getContentSize().height*2.0 / 4);
	//_labelBonus->setAnchorPoint(Vec2(0, 0.5f));
	//boardScore->addChild(_labelBonus, 100);

	//_labelBonusNum = Label::createWithTTF("", font, 40);
	//_labelBonusNum->setColor(Color3B::GREEN);
	//_labelBonusNum->setPosition(boardScore->getContentSize().width * 6 / 8, boardScore->getContentSize().height * 2 / 4);
	//_labelBonusNum->setAnchorPoint(Vec2(0.5f, 0.5f));
	//boardScore->addChild(_labelBonusNum, 100);
	///

	_labelScore = Label::createWithTTF("Score", font, 50);
	_labelScore->setColor(Color3B::RED);
	_labelScore->setPosition(boardScore->getContentSize().width / 8, boardScore->getContentSize().height * 2 / 4);
	_labelScore->setAnchorPoint(Vec2(0, 0.5f));
	boardScore->addChild(_labelScore, 100);

	_labelScoreNum = Label::createWithTTF("", font, 50);
	_labelScoreNum->setColor(Color3B::RED);
	_labelScoreNum->setPosition(boardScore->getContentSize().width * 6 / 8, boardScore->getContentSize().height * 2 / 4);
	_labelScoreNum->setAnchorPoint(Vec2(0, 0.5f));
	boardScore->addChild(_labelScoreNum, 100);

	//_labelTotal = Label::createWithTTF("Total Score", font, 50);
	//_labelTotal->setColor(Color3B::RED);
	//_labelTotal->setPosition(boardScore->getContentSize().width / 8, boardScore->getContentSize().height * 1 / 4);
	//_labelTotal->setAnchorPoint(Vec2(0, 0.5f));
	//boardScore->addChild(_labelTotal, 100);

	//_labelTotalNum = Label::createWithTTF("", font, 50);
	//_labelTotalNum->setColor(Color3B::RED);
	//_labelTotalNum->setPosition(boardScore->getContentSize().width * 6 / 8, boardScore->getContentSize().height * 1 / 4);
	//_labelTotalNum->setAnchorPoint(Vec2(0.5f, 0.5f));
	//boardScore->addChild(_labelTotalNum, 100);

	_labelPerfect->setVisible(false);
	_labelPerfectNum->setVisible(false);
	_labelBestcombo->setVisible(false);
	_labelBestcomboNum->setVisible(false);
	//_labelBonus->setVisible(false);
	//_labelBonusNum->setVisible(false);
	_labelScore->setVisible(false);
	_labelScoreNum->setVisible(false);
	//_labelTotal->setVisible(false);
	//_labelTotalNum->setVisible(false);

	//Animation Star
	star1 = Sprite::create("Finish_Layer/star.png");
	star2 = Sprite::create("Finish_Layer/star.png");
	star3 = Sprite::create("Finish_Layer/star.png");
	star1->setAnchorPoint(Vec2(0.5f, 0.5f));
	star2->setAnchorPoint(Vec2(0.5f, 0.5f));
	star3->setAnchorPoint(Vec2(0.5f, 0.5f));
	star1->setPosition(boardScore->getContentSize().width* 5.5 / 15, boardScore->getContentSize().height*1.5 / 4);
	star2->setPosition(boardScore->getContentSize().width * 7 / 15, boardScore->getContentSize().height*1.5 / 4);
	star3->setPosition(boardScore->getContentSize().width * 8.5 / 15, boardScore->getContentSize().height*1.5 / 4);
	boardScore->addChild(star1);
	boardScore->addChild(star2);
	boardScore->addChild(star3);

	star1->setOpacity(0);
	star2->setOpacity(0);
	star3->setOpacity(0);
	//End Animation Star

	//Button cancel in Board Star
	button_board_cancel = Button::create("Level_map/out.png");
	button_board_cancel->setScale(scaleX * 2, scaleY * 2);
	button_board_cancel->setAnchorPoint(Vec2(0.5f, 0.5f));
	button_board_cancel->setPosition(Vec2(boardScore->getContentSize().width * 5 / 6, -boardScore->getContentSize().height / 20));
	boardScore->addChild(button_board_cancel, 6);

	button_board_cancel->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
		{
			experimental::AudioEngine::stopAll();
			Define::_music_btn_effect_1 = experimental::AudioEngine::play2d(Define::_music_btn_effect_1_path, false, 1.0f);
			Define::_music_menu_scene_background_2 = experimental::AudioEngine::play2d(Define::_music_menu_scene_background_2_path, true, 1.0f);
			if ((SCENE_LEVELMAP)levelMap == Define::MAP_STONE) {
				auto scene = LevelMapStone::createScene();
				Director::getInstance()->replaceScene(scene);
			}
			if ((SCENE_LEVELMAP)levelMap == Define::SNOW) {
				auto scene = LevelMap::createScene();
				Director::getInstance()->replaceScene(scene);
			}
			if ((SCENE_LEVELMAP)levelMap == Define::DESERT) {
				auto scene = LevelMapDesert::createScene();
				Director::getInstance()->replaceScene(scene);
			}
		}
		break;
		default:
			break;
		}
	});

	//Start
	//Button next in Board Star
	button_board_next = Button::create("Level_map/next.png");
	button_board_next->setScale(scaleX * 2, scaleY * 2);
	button_board_next->setAnchorPoint(Vec2(0.5f, 0.5f));
	button_board_next->setPosition(Vec2(boardScore->getContentSize().width * 3 / 6, -boardScore->getContentSize().height / 20));
	boardScore->addChild(button_board_next, 6);
	button_board_next->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
		{
			Define::_music_btn_effect_1 = experimental::AudioEngine::play2d(Define::_music_btn_effect_1_path, false, 1.0f);
			if (current_scene != nullptr)
			{
				if (current_level == Define::LV0)
				{
					auto gameScene = (LoadScene*)LoadScene::createScene();
					gameScene->next_scene = Define::LV1;
					gameScene->next_scene_area = (SCENE_AREA)current_area;
					Director::getInstance()->replaceScene(TransitionFade::create(1, gameScene));
				}
				if (current_level == 1 && current_area == Define::STONE)
				{
					auto gameScene = (LoadScene*)LoadScene::createScene();
					gameScene->next_scene = Define::LV2;
					gameScene->next_scene_area = (SCENE_NAME)current_area;
					Director::getInstance()->replaceScene(TransitionFade::create(1, gameScene));
				}
			}
		}
		break;
		default:
			break;
		}
	});
	//End

	//Button round in Board Star
	button_board_round = Button::create("Level_map/round.png");
	button_board_round->setScale(scaleX * 2, scaleY * 2);
	button_board_round->setAnchorPoint(Vec2(0.5f, 0.5f));
	button_board_round->setPosition(Vec2(boardScore->getContentSize().width / 6, -boardScore->getContentSize().height / 20));
	boardScore->addChild(button_board_round, 6);
	button_board_round->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
		{
			Define::_music_btn_effect_1 = experimental::AudioEngine::play2d(Define::_music_btn_effect_1_path, false, 1.0f);
			if (current_scene != nullptr)
			{
				auto scene = (LevelScene*)current_scene;
				scene->ReloadScene();
			}
		}
		break;
		default:
			break;
		}
	});
	if (area == Define::SNOW && area == Define::DESERT) {
		button_board_next->setEnabled(false);
	}
	if (area == Define::STONE && level > Define::LV2) {
		button_board_next->setEnabled(false);
	}
	button_board_next->setVisible(false);
	button_board_cancel->setVisible(false);
	button_board_round->setVisible(false);

	this->scheduleUpdate();
}


FinishLayer::~FinishLayer()
{
}

void FinishLayer::update(float dt)
{
	//Start Count Per,Great,Bad
	if (ringCount < ring && this->isJumpPoint == true) {
		ringCount++;
		_labelRingNum->setString(to_string(ringCount));
	}
	if (per < countPerfect && ringCount == ring) {
		this->isJumpPoint = false;
		_labelPerfect->setVisible(true);
		_labelPerfectNum->setVisible(true);
		per++;
		_labelPerfectNum->setString(to_string(per));
	}
	if (bestCombo < maxCombo && per == countPerfect) {
		_labelBestcombo->setVisible(true);
		_labelBestcomboNum->setVisible(true);
		bestCombo++;
		_labelBestcomboNum->setString(to_string(bestCombo));
	}
	if (scoreCount < score && bestCombo == maxCombo) {
		_bar->setVisible(true);
		_labelScore->setVisible(true);
		_labelScoreNum->setVisible(true);
		scoreCount = score;
		_labelScoreNum->setString(to_string(scoreCount));
		auto spaw = Spawn::create(ScaleTo::create(0.2, 0.5), MoveBy::create(0.05, Vec2(20, -20)), nullptr);
		auto shake = Repeat::create(
			Sequence::create(
				MoveBy::create(0.05f, Vec2(12, 0)),
				MoveBy::create(0.05f, Vec2(-12, 0)),
				MoveBy::create(0.012f, Vec2(0, 3)),
				MoveBy::create(0.012f, Vec2(0, -3)),
				nullptr), 2);

		auto sequence = Sequence::create(spaw, shake, nullptr);

		CallFunc* star_sound = CallFunc::create([&] {
			experimental::AudioEngine::play2d(Define::_music_star_effect_path, false, 1.0f);
		});

		if (numStar == 1) {
			star1->setOpacity(255);
			star1->runAction(sequence->clone());
			this->isJumpPoint = true;
			experimental::AudioEngine::play2d(Define::_music_star_effect_path, false, 1.0f);
		}
		if (numStar == 2) {
			star1->setOpacity(255);
			star1->runAction(sequence->clone());
			star2->runAction(Sequence::create(DelayTime::create(0.25), FadeIn::create(1), sequence->clone(), nullptr));
			this->isJumpPoint = true;
			this->runAction(Sequence::create(star_sound, DelayTime::create(1.0f), star_sound, nullptr));
		}
		if (numStar == 3) {
			star1->setOpacity(255);
			star1->runAction(sequence->clone());
			star2->runAction(Sequence::create(DelayTime::create(0.25), FadeIn::create(1), sequence->clone(), nullptr));
			star3->runAction(Sequence::create(DelayTime::create(1.25), FadeIn::create(1), sequence->clone(), nullptr));
			this->isJumpPoint = true;
			this->runAction(Sequence::create(star_sound, DelayTime::create(1.0f), star_sound, DelayTime::create(1.0f), star_sound, nullptr));
		}
		if (this->isJumpPoint) {
			button_board_cancel->setVisible(true);
			button_board_round->setVisible(true);
			button_board_next->setVisible(true);
		}
		this->unscheduleUpdate();
	}

	//End Count
}