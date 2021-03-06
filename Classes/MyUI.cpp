#include "MyUI.h"
#include "TestScene.h"
#include "TurtorialScene.h"
#include "LevelMap.h"
//Start

void MyUI::SetCurrentScene(Layer * scene)
{
	current_scene = scene;
	finish->current_scene = scene;
}
void MyUI::setCurrentLevelMap(SCENE_LEVELMAP sceneLevel)
{
	currentLevelMap = sceneLevel;
	currentArea = sceneLevel;
}
void MyUI::setCurrentLevel(SCENE_NAME level)
{
	currentLevel = level;
	int abc = 0;
}
//End

void MyUI::DisableExcept(BUTTON_TAG tag)
{
	_touch_guide->setVisible(true);
	switch (tag)
	{
	case Define::BUTTON_LEFT:
		_button_right->setEnabled(false);
		_touch_guide->setPosition((_director->getWinSize().width / 3)/ 2, _director->getWinSize().height / 2);
		break;

	case Define::BUTTON_RIGHT:
		_button_left->setEnabled(false);
		_touch_guide->setPosition(_director->getWinSize().width - _director->getWinSize().width / 6, _director->getWinSize().height / 2);

		break;

	}
	_button_right->setOpacity(150);
	_button_left->setOpacity(150);
}

void MyUI::EnableAll()
{
	_button_right->setOpacity(0);
	_button_left->setOpacity(0);

	_button_left->setEnabled(true);
	_button_right->setEnabled(true);
	_touch_guide->setVisible(false);

}



MyUI::MyUI(Sonic * mSonic)
{
		this->autorelease();
		mySonic = mSonic;
		//Starting
		labelStart = Label::createWithTTF("", font, 50);
		labelStart->setString("Ready"); 
		labelStart->enableOutline(Color4B::BLACK, 3);
		labelStart->setPosition(_director->getWinSize().width /2 , _director->getWinSize().height/2);
		labelStart->setAnchorPoint(Vec2(0.5f,0.5f));
		this->addChild(labelStart,10);

		layer_1 = LayerColor::create();
		layer_1->setColor(Color3B::BLACK);
		layer_1->setOpacity(210);
		this->addChild(layer_1,9);

		layer = LayerColor::create();
		layer->setColor(Color3B::BLACK);
		layer->setOpacity(200);
		layer->setVisible(false);
		this->addChild(layer);

		//scene->MyReadyPause();
		//End
		_touch_guide = Sprite::create();
		auto animation = Animation::createWithSpriteFrames(Define::loadAnim("GameComponents/touch.xml", "1"), 0.03f);
		_touch_guide->runAction(RepeatForever::create(Animate::create(animation)));
		_touch_guide->setVisible(false);
		_touch_guide->setScale(0.6);
		_touch_guide->setAnchorPoint(Vec2(0.5, 0.5));
		this->addChild(_touch_guide);

		_button_left = Button::create(Define::button_left_grey_path);
		float delta_scale_x = (_director->getWinSize().width / 3)/_button_left->getContentSize().width;
		float delta_scale_y= _director->getWinSize().height / _button_left->getContentSize().height;

		_button_left->setScale(delta_scale_x, delta_scale_y);
		_button_left->setOpacity(0);
		_button_left->setPosition(Vec2(_button_left->getContentSize().width*delta_scale_x/2, 0));
		_button_left->setAnchorPoint(Vec2(0.5, 0));

		_button_left->addTouchEventListener([this](Ref* sender, Widget::TouchEventType type) {
			auto but = (Button*)sender;
			switch (type)
			{
			case ui::Widget::TouchEventType::BEGAN:
			//	but->setOpacity(255);
				break;
			case ui::Widget::TouchEventType::ENDED:
			//	but->setOpacity(200);
			
				mySonic->ActiveButton(BUTTON_TAG::BUTTON_LEFT);
				Define::_music_tap_button_effect = experimental::AudioEngine::play2d(Define::_music_tap_button_effect_path, false, 1.0f);
				break;
			default:
				break;
			}
		});
	
		this->addChild(_button_left, -1);



		_button_right = Button::create(Define::button_right_grey_path);
		_button_right->setScale(delta_scale_x, delta_scale_y);
		_button_right->setPosition(Vec2(_director->getWinSize().width - _button_left->getContentSize().width*delta_scale_x / 2, 0));
		_button_right->setAnchorPoint(Vec2(0.5, 0));
		_button_right->setOpacity(0);
		_button_right->addTouchEventListener([this](Ref* sender, Widget::TouchEventType type) {
			auto but = (Button*)sender;
			switch (type)
			{
			case ui::Widget::TouchEventType::BEGAN:
				//but->setOpacity(255);
				break;
			case ui::Widget::TouchEventType::ENDED:
					mySonic->ActiveButton(BUTTON_TAG::BUTTON_RIGHT);
					Define::_music_tap_button_effect = experimental::AudioEngine::play2d(Define::_music_tap_button_effect_path, false, 1.0f);
					
				//but->setOpacity(200);
				break;
			default:
				break;
			}
		});
		this->addChild(_button_right, -1);

		//visibleSzie level map
		auto visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();
		float scaleX = visibleSize.width / 2;
		float scaleY = visibleSize.height / 2;

		//Board Star
		board = Sprite::create("Level_map/game_board.png");
		//board->setScale(origin.x /2, origin.y /2);
		board->setAnchorPoint(Vec2(0.5f, 0.5f));
		board->setOpacity(0);
		board->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
		board->setVisible(false);
		this->addChild(board, 5);

		//Define delta x size board
		float delta_x = board->getContentSize().width / 10;
		float delta_y = board->getContentSize().height * 2 / 5;
		//Define number scale button in Board Star
		float numScale = 0.9;

		//Label Board Star
		auto myLabel = Label::createWithTTF("Pause", font, 30);
		myLabel->setAnchorPoint(Vec2(0.5f, 0.5f));
		myLabel->setPosition(Vec2(delta_x * 6 - delta_x * 2 / 2, delta_y * 2.5 - delta_y / 2));
		board->addChild(myLabel, 2);

		//Button round in Board Star
		auto button_board_round = Button::create("Level_map/round.png");
		//button_board_round->setScale(numScale*scaleX, numScale*scaleY);
		button_board_round->setAnchorPoint(Vec2(0.5f, 0.5f));
		button_board_round->setPosition(Vec2(delta_x * 2 / 2, delta_y));
		board->addChild(button_board_round, 6);
		button_board_round->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
			switch (type)
			{
			case ui::Widget::TouchEventType::BEGAN:
				break;
			case ui::Widget::TouchEventType::ENDED:
			{
				Define::_music_btn_effect_1 = experimental::AudioEngine::play2d(Define::_music_btn_effect_1_path, false, 1.0f);
				_restart->setVisible(true);
				board->setVisible(false);
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

		//Button play  in Board Star
		auto button_board_play = Button::create("Level_map/play.png");
		//button_board_play->setScale(numScale*scaleX, numScale*scaleY);
		button_board_play->setAnchorPoint(Vec2(0.5f, 0.5f));
		button_board_play->setPosition(Vec2(delta_x * 10 / 2, delta_y));
		board->addChild(button_board_play, 6);
		button_board_play->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
			switch (type)
			{
			case ui::Widget::TouchEventType::BEGAN:
				break;
			case ui::Widget::TouchEventType::ENDED:
			{
				experimental::AudioEngine::resumeAll();
				Define::_music_btn_effect_1 = experimental::AudioEngine::play2d(Define::_music_btn_effect_1_path, false, 1.0f);
				/*isPause = false;*/
				_restart->setVisible(true);
				board->setVisible(false);
				layer->setVisible(false);
				if (current_scene != nullptr)
				{
					auto scene = (LevelScene*)current_scene;
					scene->MyResume();
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
		button_board_cancel->setPosition(Vec2(delta_x * 19 / 2, delta_y));
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
				_restart->setVisible(true);
				board->setVisible(false);
				layer->setVisible(false);
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

		_restart = Button::create("Level_map/pause.png");
		_restart->setPosition(Vec2(_director->getWinSize().width - _restart->getContentSize().width, _director->getWinSize().height - 0.5 * _restart->getContentSize().height));
		_restart->setScale(0.8);
		_restart->setAnchorPoint(Vec2(0.5, 0.5));
		_restart->addTouchEventListener([this](Ref* sender, Widget::TouchEventType type) {
			auto but = (Button*)sender;
			switch (type)
			{
			case ui::Widget::TouchEventType::BEGAN:
				break;
			case ui::Widget::TouchEventType::ENDED: 
			{
				experimental::AudioEngine::pauseAll();
				Define::_music_btn_effect_1 = experimental::AudioEngine::play2d(Define::_music_btn_effect_1_path, false, 1.0f);
				_restart->setVisible(false);
				board->setVisible(true);
				layer->setVisible(true);
				if (current_scene != nullptr)
				{
					auto scene = (LevelScene*)current_scene;
					scene->MyPause();
				}
			}
				break;
			default:
				break;
			}
		});
		this->addChild(_restart, -1);

		//Add label Ring-Combo-Score
		_combo = new RingComboScore(mSonic);
		this->addChild(_combo, 1);
		
		touch_ani = new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(Define::loadAnim("GameComponents/ripple.xml","1"), 0.008f)));
		auto listener1 = EventListenerTouchOneByOne::create();

		listener1->onTouchBegan = [this](Touch* touch, Event* event) {
			//start_touch_position = touch->getLocation();
			return true;
		};

		// trigger when you let up
		listener1->onTouchEnded = [this](Touch* touch, Event* event) {
			auto sprite = Sprite::create();
			sprite->setScale(0.7);
			sprite->setOpacity(200);
			sprite->setPosition(touch->getLocation());
			this->getParent()->addChild(sprite);
			sprite->runAction(Sequence::create(touch_ani->get()->clone(), RemoveSelf::create(), nullptr));
			_istouch = true;
			
		};

		auto eventListener = EventListenerKeyboard::create();
		eventListener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event) {
	


		};
		eventListener->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event* event) {

			if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW)
			{
			/*	auto scene =(LevelScene*) current_scene;
				scene->NextScene();*/


				mySonic->ActiveButton(BUTTON_TAG::BUTTON_LEFT);
			}
			else if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
			{
			//	mySonic->mJustTap = BUTTON_TAG::BUTTON_RIGHT;
				mySonic->ActiveButton(BUTTON_TAG::BUTTON_RIGHT);
			}

		};
		_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener, this);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, this);
	//	this->autorelease();
		this->scheduleUpdate();
};

void MyUI::update(float dt)
{

	if (mySonic->isCollision == true && currentLevel != Define::LV0 && currentLevel != Define::LV2) {
		if (isCallPause == false) {
			auto scene = (LevelScene*)current_scene;
			scene->MyReadyPause();
			isCallPause = true;
			_restart->setVisible(false);
		}
		if (isDone == false) {
			if (isReady == true) {
				count_ready++;
				if (count_ready == 90) {
					//AlrightNow voice
					if (isTurnOnMusic1 == false) {
						experimental::AudioEngine::play2d(Define::_music_voice_start_1_path, false, 1.0f);
						isTurnOnMusic1 = true;
					}
					isReady = false;
					isStart = true;
					labelStart->setString("Start");
				}
			}
			if (isStart == true) {
				count_start++;
				if (count_start == 60) {
					//ComeOn voice
					if (isTurnOnMusic2 == false) {
						experimental::AudioEngine::play2d(Define::_music_voice_start_2_path, false, 1.0f);
						isTurnOnMusic2 = true;
					}
					isStart = false;
					isCount = true;
					labelStart->setString("Go!");
				}
			}
			if (isCount == true) {
				count_number++;
			}
			//if (count_number == 45) {
			//	labelStart->setString("2");
			//}
			//if (count_number == 90) {
			//	labelStart->setString("1");
			//}
			if (count_number == 60) {
				isCount = false;
				isDone = true;
				labelStart->setVisible(false);
				layer_1->setOpacity(0);
				layer_1->setVisible(false);
				this->removeChild(layer_1);
				mySonic->isCollision = false;
				auto scene = (LevelScene*)current_scene;
				scene->MyReadyResume();
				_restart->setVisible(true);
			}
		}
	}
	if (currentLevel == Define::LV0 || currentLevel == Define::LV2) {
		labelStart->setVisible(false);
		layer_1->setOpacity(0);
		layer_1->setVisible(false);
	}
	count_to_reset_touch++;
	if (count_to_reset_touch ==5)
	{
		count_to_reset_touch = 0;
		_istouch = false;
	}

	if (mySonic->isFinish)
	{
		count_to_finish++;
		_restart->setVisible(false);
		if (count_to_finish >= 150)
		{
			_combo->removeAllChildren();
			_combo->unscheduleUpdate();
			finish = new FinishLayer(mySonic, current_scene, currentLevelMap);
			finish->current_area = currentArea;
			finish->current_level = currentLevel;
			this->addChild(finish, 100);
			layer = LayerColor::create();
			layer->setColor(Color3B::BLACK);
			layer->setOpacity(200);
			this->addChild(layer);
			layer->setVisible(true);
			mySonic->isFinish = false;
		}
	}

	if (mySonic->isGameOver)
	{
		_restart->setVisible(false);
		count_to_gameover++;
		if (count_to_gameover >= 60)
		{
			experimental::AudioEngine::stopAll();
			Define::_music_game_over_effect_1 = experimental::AudioEngine::play2d(Define::_music_game_over_effect_1_path, false, 1.0f);

			_istouch = false;
			_combo->removeAllChildren();
			_combo->unscheduleUpdate();
			gameover = new GameOverLayer(mySonic, current_scene,currentLevelMap);
			this->addChild(gameover, 100);

			layer = LayerColor::create();
			layer->setColor(Color3B::BLACK);
			layer->setOpacity(200);
			this->addChild(layer);
			layer->setVisible(true);
			mySonic->isGameOver = false;
		}
	}
}