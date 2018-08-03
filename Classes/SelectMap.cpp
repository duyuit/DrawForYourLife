#include "SelectMap.h"



SelectMap::SelectMap()
{
}


SelectMap::~SelectMap()
{
}

bool SelectMap::init()
{

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	visibleSize.width = visibleSize.width *1.5;

	auto background = Sprite::create("Select_map/background.jpg");
	background->setScale(visibleSize.width / (background->getContentSize().width), visibleSize.height / (background->getContentSize().height));
	background->setAnchorPoint(Vec2(0.5f, 0.5f));
	background->setPosition(Vec2(visibleSize.width / 3, visibleSize.height / 2));
	this->addChild(background, -1);
	Text* label0 = Text::create("Select Area", font, 50);
	label0->setColor(Color3B::WHITE);
	label0->setPosition(Vec2(visibleSize.width / 3, visibleSize.height*1.7 / 2));
	this->addChild(label0, 3);

	auto effect_background = ParticleSystemQuad::create("Select_map/background_effect.plist");
	this->addChild(effect_background, 0);

	//////
	_btn_map_1 = Button::create("Select_map/stone_background.png");
	_btn_map_1->setAnchorPoint(Vec2(0.5f, 0.5f));
	_btn_map_1->setPosition(Vec2(visibleSize.width / 3, visibleSize.height / 2));
	_btn_map_1->setScale(0.8, 0.8);
	_btn_map_1->addTouchEventListener(CC_CALLBACK_2(SelectMap::load, this));
	this->addChild(_btn_map_1, 1);
	label1 = Text::create("Stone", font, 30);
	label1->setColor(Color3B::WHITE);
	label1->setPosition(Vec2(visibleSize.width / 3, visibleSize.height / 1.3));
	this->addChild(label1, 2);

	_btn_map_2 = Button::create("Select_map/snow_background.png");
	_btn_map_2->setAnchorPoint(Vec2(0.5f, 0.5f));
	_btn_map_2->setPosition(Vec2(visibleSize.width / 3, visibleSize.height / 2));
	_btn_map_2->setScale(0.8, 0.8);
	_btn_map_2->addTouchEventListener(CC_CALLBACK_2(SelectMap::load, this));
	_btn_map_2->setVisible(false);
	this->addChild(_btn_map_2, 1);
	label2 = Text::create("Winter", font, 30);
	label2->setColor(Color3B::WHITE);
	label2->setPosition(Vec2(visibleSize.width / 3, visibleSize.height / 1.3));
	this->addChild(label2, 2);
	label1->setVisible(false);

	_btn_map_3 = Button::create("Select_map/desert_background.png");
	_btn_map_3->setAnchorPoint(Vec2(0.5f, 0.5f));
	_btn_map_3->setPosition(Vec2(visibleSize.width / 3, visibleSize.height / 2));
	_btn_map_3->setScale(0.8, 0.8);
	_btn_map_3->addTouchEventListener(CC_CALLBACK_2(SelectMap::load, this));
	_btn_map_3->setVisible(false);
	this->addChild(_btn_map_3, 1);
	label3 = Text::create("Desert", font, 30);
	label3->setColor(Color3B::WHITE);
	label3->setPosition(Vec2(visibleSize.width / 3, visibleSize.height / 1.3));
	this->addChild(label3, 2);
	label3->setVisible(false);



	btn_right = Button::create("Select_map/arrow_right_ready.png", "Select_map/arrow_right.png");
	btn_right->addTouchEventListener(CC_CALLBACK_2(SelectMap::nextPage, this));
	btn_right->setAnchorPoint(Vec2(0.5f, 0.5f));
	btn_right->setPosition(Vec2(visibleSize.width / (1.62), visibleSize.height / 2.2));
	this->addChild(btn_right, 3);
	btn_left = Button::create("Select_map/arrow_left_ready.png", "Select_map/arrow_left.png");
	btn_left->addTouchEventListener(CC_CALLBACK_2(SelectMap::backPage, this));
	btn_left->setAnchorPoint(Vec2(0.5f, 0.5f));
	btn_left->setPosition(Vec2(visibleSize.width / (19.5), visibleSize.height / 2.2));
	btn_left->setVisible(false);
	this->addChild(btn_left, 3);

	this->scheduleUpdate();
	return true;
}


void SelectMap::nextPage(Ref* sender, ui::Widget::TouchEventType type) {
	/*_currentPage = (int)_pageView->getCurrentPageIndex();*/
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		break;
	case cocos2d::ui::Widget::TouchEventType::ENDED: {
		SimpleAudioEngine::getInstance()->playEffect(Define::_music_btn_arrow_effect_path);
		_currentPage++;
	}
													 break;
	default:
		break;
	}

	/*_pageView->scrollToPage(_currentPage);*/
}
void SelectMap::backPage(Ref* sender, ui::Widget::TouchEventType type) {
	/*_currentPage = (int)_pageView->getCurrentPageIndex();*/
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		break;
	case cocos2d::ui::Widget::TouchEventType::ENDED: {
		SimpleAudioEngine::getInstance()->playEffect(Define::_music_btn_arrow_effect_path);
		_currentPage--;
	}
													 break;
	default:
		break;
	}
	/*_pageView->scrollToPage(_currentPage);*/

}
cocos2d::Scene * SelectMap::createScene()
{
	return SelectMap::create();
}
void SelectMap::load(Ref* sender, ui::Widget::TouchEventType type) {
	SimpleAudioEngine::getInstance()->playEffect(Define::_music_btn_effect_1_path);
	if (_currentPage == 0) {
		auto scene = LevelMapStone::createScene();
		Director::getInstance()->replaceScene(TransitionFade::create(1, scene));
	}
	if (_currentPage == 1) {
		auto scene = LevelMap::createScene();
		Director::getInstance()->replaceScene(TransitionFade::create(1, scene));
	}
	if (_currentPage == 2) {
		auto scene = LevelMapDesert::createScene();
		Director::getInstance()->replaceScene(TransitionFade::create(1, scene));
	}
}
void SelectMap::update(float dt) {
	if (_currentPage == 1) {
		_btn_map_3->setVisible(false);
		_btn_map_1->setVisible(false);
		_btn_map_2->setVisible(true);
		label3->setVisible(false);
		label1->setVisible(false);
		label2->setVisible(true);
		btn_left->setVisible(true);
		btn_right->setVisible(true);
	}
	if (_currentPage == 0) {
		_btn_map_2->setVisible(false);
		_btn_map_3->setVisible(false);
		_btn_map_1->setVisible(true);
		label3->setVisible(false);
		label2->setVisible(false);
		label1->setVisible(true);
		btn_right->setVisible(true);
		btn_left->setVisible(false);
	}
	if (_currentPage == 2) {
		_btn_map_1->setVisible(false);
		_btn_map_2->setVisible(false);
		_btn_map_3->setVisible(true);
		label2->setVisible(false);
		label1->setVisible(false);
		label3->setVisible(true);
		btn_left->setVisible(true);
		btn_right->setVisible(false);
	}
}