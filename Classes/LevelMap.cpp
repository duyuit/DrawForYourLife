#include "LevelMap.h"
using namespace std;
using namespace ui;

cocos2d::Scene * LevelMap::createScene()
{
	return LevelMap::create();
}

LevelMap::LevelMap()
{
}

bool LevelMap::init()
{
	if (!Scene::init())
	{
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();


	//background 
	auto background = Sprite::create("Level_map/cloud.jpg");
	background->setScale(visibleSize.width / (background->getContentSize().width), visibleSize.height / (background->getContentSize().height));
	background->setAnchorPoint(Vec2(0.5, 0.5));
	background->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(background, 0);

	//level map
	auto loading = Sprite::create("Level_map/level_map_snow1.png");
	loading->setScale(visibleSize.width / (loading->getContentSize().width * 2), visibleSize.height / (loading->getContentSize().height * 2));
	loading->setAnchorPoint(Vec2(0.5, 0.5));
	loading->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(loading, 1);

	//visibleSzie level map
	float scaleX = visibleSize.width / (loading->getContentSize().width * 2);
	float scaleY = visibleSize.height / (loading->getContentSize().height * 2);

	//Board Star
	board = Sprite::create("Level_map/game_board.png");
	board->setScale(scaleX, scaleY);
	board->setAnchorPoint(Vec2(0.5f, 0.5f));
	board->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	board->setVisible(false);
	this->addChild(board, 5);

	//Define delta x size board
	float delta_x = board->getContentSize().width / 5;
	float delta_y = board->getContentSize().height / 5;

	//Define number scale button in Board Star
	float numScale = 0.9;

	//Gray Star
	auto gray_star_1 = Sprite::create("Level_map/star_ready.png");
	gray_star_1->setScale(scaleX, scaleY);
	gray_star_1->setAnchorPoint(Vec2(0.5f, 0.5f));
	gray_star_1->setPosition(Vec2(delta_x * 3 / 2, delta_y * 5 - delta_y / 2));
	star_list.pushBack(gray_star_1);

	auto gray_star_2 = Sprite::create("Level_map/star_ready.png");
	gray_star_2->setScale(scaleX, scaleY);
	gray_star_2->setAnchorPoint(Vec2(0.5f, 0.5f));
	gray_star_2->setPosition(Vec2(delta_x * 5 / 2, delta_y * 5 - delta_y / 3));
	star_list.pushBack(gray_star_2);

	auto gray_star_3 = Sprite::create("Level_map/star_ready.png");
	gray_star_3->setScale(scaleX, scaleY);
	gray_star_3->setAnchorPoint(Vec2(0.5f, 0.5f));
	gray_star_3->setPosition(Vec2(delta_x * 7 / 2, delta_y * 5 - delta_y / 2));
	star_list.pushBack(gray_star_3);

	board->addChild(gray_star_1, 2);
	board->addChild(gray_star_2, 2);
	board->addChild(gray_star_3, 2);

	//Label level in Board Star
	myLabel = Label::createWithTTF("", "fonts/arial.ttf", 30);
	myLabel->setAnchorPoint(Vec2(0.5f, 0.5f));
	myLabel->setPosition(Vec2(delta_x * 3 - delta_x / 2, delta_y * 4 - delta_y / 2));
	board->addChild(myLabel, 2);




	//Button round in Board Star
	auto button_board_round = Button::create("Level_map/round.png");
	button_board_round->setScale(numScale*scaleX, numScale*scaleY);
	button_board_round->setAnchorPoint(Vec2(0.5f, 0.5f));
	button_board_round->setPosition(Vec2(delta_x * 3 / 2, delta_y));
	board->addChild(button_board_round, 6);
	button_board_round->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
		{

		}
		break;
		default:
			break;
		}
	});

	//Button play  in Board Star
	auto button_board_play = Button::create("Level_map/play.png");
	button_board_play->setScale((numScale*scaleX) / 2, (numScale*scaleY) / 2);
	button_board_play->setAnchorPoint(Vec2(0.5f, 0.5f));
	button_board_play->setPosition(Vec2(delta_x * 5 / 2, delta_y));
	board->addChild(button_board_play, 6);
	button_board_play->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
		{
			auto gameScene =(LoadScene*) LoadScene::createScene();
			gameScene->next_scene = (SCENE_NAME)currentLevel;
			Director::getInstance()->replaceScene(TransitionFade::create(1, gameScene));
			/*if (currentLevel == 0) {
				
			}
			if (currentLevel > 0) {
				auto gameScene = Level1Scene::createScene();
				Director::getInstance()->replaceScene(TransitionFade::create(1, gameScene));
			}*/
		}
		break;
		default:
			break;
		}
	});

	//Button cancel in Board Star
	auto button_board_cancel = Button::create("Level_map/out.png");
	button_board_cancel->setScale(numScale*scaleX, numScale*scaleY);
	button_board_cancel->setAnchorPoint(Vec2(0.5f, 0.5f));
	button_board_cancel->setPosition(Vec2(delta_x * 7 / 2, delta_y));
	board->addChild(button_board_cancel, 6);

	button_board_cancel->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
		{
			board->setVisible(false);
		}
		break;
		default:
			break;
		}
	});

	//Define number Scale button in Level Map
	float levelScale = 1.5;


	//button back
	auto button_back = Button::create("Level_map/back.png");
	button_back->setAnchorPoint(Vec2(0.5f, 0.5f));
	button_back->setPosition(Vec2(visibleSize.width / 20, 0.96*visibleSize.height));
	button_back->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
		{
			auto gameScene = SelectMap::createScene();
			Director::getInstance()->replaceScene(TransitionFade::create(1, gameScene));
		}
		break;
		default:
			break;
		}
	});
	this->addChild(button_back, 50);


	// Level 0 button
	auto button_level_0 = Button::create("Level_map/level_btn_bluepurple_big.png");
	button_level_0->setScale(levelScale * scaleX, levelScale * scaleY);
	button_level_0->setAnchorPoint(Vec2(0.5f, 0.5f));
	button_level_0->runAction(RepeatForever::create(Sequence::create(MoveBy::create(1, Vec2(0, 7)), MoveBy::create(1, Vec2(0, -7)), nullptr)));
	button_level_0->setPosition(Vec2(visibleSize.width / 1.5f, 0.5f*visibleSize.height));
	button_level_0->addTouchEventListener([this](Ref* sender, Widget::TouchEventType type) {
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
		{
			setStar(0, 0);// pos 0 - 2 star
			board->setVisible(true);

		}
		break;
		default:
			break;
		}
	});
	this->addChild(button_level_0, 2);

	_label_0 = Label::createWithTTF("0", "fonts/arial.ttf", 30);
	_label_0->setAnchorPoint(Vec2(0.5f, 0.5f));
	_label_0->setPosition(Vec2(visibleSize.width / 1.51f, 0.505f*visibleSize.height));
	_label_0->runAction(RepeatForever::create(Sequence::create(MoveBy::create(1, Vec2(0, 7)), MoveBy::create(1, Vec2(0, -7)), nullptr)));
	this->addChild(_label_0, 3);

	// Level 1 button
	auto button_level_1 = Button::create("Level_map/level_btn_bluepurple_big.png");
	button_level_1->setScale(levelScale * scaleX, levelScale * scaleY);
	button_level_1->setAnchorPoint(Vec2(0.5f, 0.5f));
	button_level_1->runAction(RepeatForever::create(Sequence::create(MoveBy::create(1, Vec2(0, 7)), MoveBy::create(1, Vec2(0, -7)), nullptr)));
	button_level_1->setPosition(Vec2(visibleSize.width / 1.87f, 0.58f*visibleSize.height));
	button_level_1->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
		{
			setStar(1, 0); // pos 1 - 1 star
			board->setVisible(true);
		}
		break;
		default:
			break;
		}
	});
	this->addChild(button_level_1, 2);

	_label_1 = Label::createWithTTF("1", "fonts/arial.ttf", 30);
	_label_1->setAnchorPoint(Vec2(0.5f, 0.5f));
	_label_1->setPosition(Vec2(visibleSize.width / 1.88f, 0.585f*visibleSize.height));
	_label_1->runAction(RepeatForever::create(Sequence::create(MoveBy::create(1, Vec2(0, 7)), MoveBy::create(1, Vec2(0, -7)), nullptr)));
	this->addChild(_label_1, 3);

	// Level 2 button
	auto button_level_2 = Button::create("Level_map/level_btn_bluepurple_big.png");
	button_level_2->setScale(levelScale * scaleX, levelScale * scaleY);
	button_level_2->setAnchorPoint(Vec2(0.5f, 0.5f));
	button_level_2->runAction(RepeatForever::create(Sequence::create(MoveBy::create(1, Vec2(0, 7)), MoveBy::create(1, Vec2(0, -7)), nullptr)));
	button_level_2->setPosition(Vec2(visibleSize.width / 2.55f, 0.6f*visibleSize.height));
	button_level_2->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
		{
			setStar(2, 0); // level 2 - 3 star
			board->setVisible(true);
		}
		break;
		default:
			break;
		}
	});
	this->addChild(button_level_2, 2);

	// Level 3 button
	auto button_level_3 = Button::create("Level_map/level_btn_bluepurple_big.png");
	button_level_3->setScale(levelScale * scaleX, levelScale * scaleY);
	button_level_3->setAnchorPoint(Vec2(0.5f, 0.5f));
	button_level_3->runAction(RepeatForever::create(Sequence::create(MoveBy::create(1, Vec2(0, 7)), MoveBy::create(1, Vec2(0, -7)), nullptr)));
	button_level_3->setPosition(Vec2(visibleSize.width / 2.25f, 0.454f*visibleSize.height));
	button_level_3->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
		{
			setStar(3, 0); // level 3 - 3 star
			board->setVisible(true);
		}
		break;
		default:
			break;
		}
	});
	this->addChild(button_level_3, 2);

	// Level 4 button
	auto button_level_4 = Button::create("Level_map/level_btn_bluepurple_big.png");
	button_level_4->setScale(levelScale * scaleX, levelScale * scaleY);
	button_level_4->setAnchorPoint(Vec2(0.5f, 0.5f));
	button_level_4->runAction(RepeatForever::create(Sequence::create(MoveBy::create(1, Vec2(0, 7)), MoveBy::create(1, Vec2(0, -7)), nullptr)));
	button_level_4->setPosition(Vec2(visibleSize.width / 2.0f, 0.357f*visibleSize.height));
	button_level_4->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
		{
			setStar(4, 0); // level 4 - 3 star
			board->setVisible(true);
		}
		break;
		default:
			break;
		}
	});
	this->addChild(button_level_4, 2);

	// Level 5 button
	auto button_level_5 = Button::create("Level_map/level_btn_bluepurple_big.png");
	button_level_5->setScale(levelScale * scaleX, levelScale * scaleY);
	button_level_5->setAnchorPoint(Vec2(0.5f, 0.5f));
	button_level_5->runAction(RepeatForever::create(Sequence::create(MoveBy::create(1, Vec2(0, 7)), MoveBy::create(1, Vec2(0, -7)), nullptr)));
	button_level_5->setPosition(Vec2(visibleSize.width / 1.75f, 0.33f*visibleSize.height));
	button_level_5->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
		{
			setStar(5, 0); // level 5 - 3 star
			board->setVisible(true);
		}
		break;
		default:
			break;
		}
	});
	this->addChild(button_level_5, 2);

	// Level Bonus button
	auto button_level_bonus = Button::create("Level_map/level_btn_bluepurple_big.png");
	button_level_bonus->setScale(levelScale * scaleX, levelScale * scaleY);
	button_level_bonus->setAnchorPoint(Vec2(0.5f, 0.5f));
	button_level_bonus->runAction(RepeatForever::create(Sequence::create(MoveBy::create(1, Vec2(0, 7)), MoveBy::create(1, Vec2(0, -7)), nullptr)));
	button_level_bonus->setPosition(Vec2(visibleSize.width / 2.7f, 0.4*visibleSize.height));
	button_level_bonus->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
		{
			setStar(6, 0); // level bonus - 3 star
			board->setVisible(true);
		}
		break;
		default:
			break;
		}
	});

	this->addChild(button_level_bonus, 2);
	return true;
}

void LevelMap::nextScene(cocos2d::Node* sender)
{
	//auto gameScene = GamePlayScense::createScene();
	//Director::getInstance()->replaceScene(TransitionFade::create(1, gameScene));

}

LevelMap::~LevelMap()
{
}
void LevelMap::setStar(int level, int star) {
	currentLevel = level;
	for (int i = 0; i < 3; i++)
	{
		if (i<star)
			star_list.at(i)->initWithFile("Level_map/star.png");
		else
			star_list.at(i)->initWithFile("Level_map/star_ready.png");
	}

	_levelState = level;
	string str = "";
	if (_levelState != 6) {
		str = "Level " + std::to_string(_levelState) + "\nStar " + std::to_string(star);
	}
	else {
		str = "Level Bonus \n Star " + std::to_string(star);
	}
	myLabel->setString(str);
}



