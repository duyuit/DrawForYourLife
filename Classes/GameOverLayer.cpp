#include "GameOverLayer.h"
#include "LevelScene.h"
#include "SelectMap.h"

GameOverLayer::GameOverLayer(Sonic* mSonic, Layer* cur_scene,SCENE_LEVELMAP cur_levelmap)
{
	this->autorelease();
	mySonic = mSonic;
	MyUI* myUI = new MyUI();
	current_scene = cur_scene;
	currentLevelMap = cur_levelmap;
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//Board Star
	board = Sprite::create("Level_map/game_board.png");
	//board->setScale(origin.x /2, origin.y /2);
	board->setAnchorPoint(Vec2(0.5f, 0.5f));
	board->setOpacity(0);
	board->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(board, 5);

	_gameover = Label::createWithTTF("GAME OVER", font, 75);
	_gameover->setColor(Color3B::WHITE);
	_gameover->enableOutline(Color4B::BLACK, 5);
	_gameover->setPosition(board->getContentSize().width / 2, board->getContentSize().height*3.5 / 4);
	board->addChild(_gameover, 100);




	//Define delta x size board
	float delta_x = board->getContentSize().width / 10;
	float delta_y = board->getContentSize().height * 2 / 5;

	//Button round in Board Star
	auto button_board_round = Button::create("Level_map/round.png");
	//button_board_round->setScale(numScale*scaleX, numScale*scaleY);
	button_board_round->setAnchorPoint(Vec2(0.5f, 0.5f));
	button_board_round->setPosition(Vec2(delta_x * 4 / 2, delta_y));
	board->addChild(button_board_round, 6);
	button_board_round->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
		{
			experimental::AudioEngine::stopAll();
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


	//Button cancel in Board Star
	auto button_board_cancel = Button::create("Level_map/out.png");
	//button_board_cancel->setScale(numScale*scaleX, numScale*scaleY);
	button_board_cancel->setAnchorPoint(Vec2(0.5f, 0.5f));
	button_board_cancel->setPosition(Vec2(delta_x * 15 / 2, delta_y));
	board->addChild(button_board_cancel, 6);

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
			//setEnabledAll(true);
			if (currentLevelMap == Define::MAP_STONE) {
				Director::getInstance()->replaceScene(LevelMapStone::createScene());
			}
			if (currentLevelMap == Define::MAP_SNOW) {
				Director::getInstance()->replaceScene(LevelMap::createScene());
			}
			if (currentLevelMap == Define::MAP_DESERT) {
				Director::getInstance()->replaceScene(LevelMapDesert::createScene());
			}

		}
		break;
		default:
			break;
		}
	});
}


GameOverLayer::~GameOverLayer()
{
}
