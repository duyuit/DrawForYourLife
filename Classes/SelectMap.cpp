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
	background->setScale(1.35);
	background->setAnchorPoint(Vec2(0.5f, 0.5f));
	background->setPosition(Vec2(visibleSize.width/3,visibleSize.height/2));
	this->addChild(background, -1);

	Text* label0 = Text::create("Select Area", "fonts/hemi.ttf", 50);
	label0->setColor(Color3B::WHITE);
	label0->setPosition(Vec2(visibleSize.width / 3, visibleSize.height*1.7/2));
	this->addChild(label0, 6);

	auto effect_background = ParticleSystemQuad::create("Select_map/background_effect.plist");
	this->addChild(effect_background, 0);
	// Create the page view
	Size pageViewSize(visibleSize.width/2, visibleSize.height);
	Size pageSize(150, 150);
	 _pageView = PageView::create();
	 _pageView->setDirection(PageView::Direction::HORIZONTAL);
	 _pageView->setContentSize(pageViewSize);
	 _pageView->setBounceEnabled(true);
	Size backgroundSize = visibleSize/2;
	_pageView->setPosition(Vec2(visibleSize.width / 3, visibleSize.height / 2));
	_pageView->setAnchorPoint(Vec2(0.5f, 0.5f));
	_pageView->setItemsMargin(10);
	_pageView->removeAllItems();
	_pageView->setGlobalZOrder(200);

	string str;
	for (int i = 1; i <= 3; ++i)
	{
		Layout* layout = Layout::create();
		layout->setContentSize(pageSize);

		Layout* layout1 = Layout::create();
		layout1->setContentSize(pageSize);

		Layout* layout2 = Layout::create();
		layout2->setContentSize(pageSize);
		if (i == 1) {
			_btn_map_1 = Button::create("Select_map/stone_background.png");
			_btn_map_1->setAnchorPoint(Vec2(0.5f, 0.5f));
			_btn_map_1->setPosition(Vec2(visibleSize.width/ 4, visibleSize.height / 2));
			Text* label = Text::create("Stone", "fonts/hemi.ttf", 30);
			label->setColor(Color3B::WHITE);
			label->setPosition(Vec2(visibleSize.width/ 4, visibleSize.height*1.5/2));
			layout->addChild(label, 2);
			layout->addChild(_btn_map_1);
		}
		if (i == 2) {
			_btn_map_2 = Button::create("Select_map/snow_background.png");
			_btn_map_2->setAnchorPoint(Vec2(0.5f, 0.5f));
			_btn_map_2->setPosition(Vec2(visibleSize.width/ 4, visibleSize.height / 2));
			_btn_map_2->addTouchEventListener(CC_CALLBACK_2(SelectMap::load, this));

			Text* label = Text::create("Snow", "fonts/hemi.ttf", 30);
			label->setColor(Color3B::WHITE);
			label->setPosition(Vec2(visibleSize.width/ 4, visibleSize.height*1.5/2));
			layout->addChild(label, 2);
			layout->addChild(_btn_map_2);
		}
		if (i == 3) {
			_btn_map_3 = Button::create("Select_map/desert_background.png");
			_btn_map_3->setAnchorPoint(Vec2(0.5f, 0.5f));
			_btn_map_3->setPosition(Vec2(visibleSize.width/ 4, visibleSize.height / 2));
			Text* label = Text::create("Desert", "fonts/hemi.ttf", 30);
			label->setColor(Color3B::WHITE);
			label->setPosition(Vec2(visibleSize.width/ 4, visibleSize.height*1.5 / 2));
			layout->addChild(label, 2);
			layout->addChild(_btn_map_3);
		}

		_pageView->addPage(layout);
		str = to_string(i);
	}
	this->addChild(_pageView,1);

	auto btn_right = Button::create("Select_map/arrow_right_ready.png","Select_map/arrow_right.png");
	btn_right->addTouchEventListener(CC_CALLBACK_2(SelectMap::nextPage, this));
	btn_right->setAnchorPoint(Vec2(0.5f, 0.5f));
	btn_right->setPosition(Vec2(visibleSize.width /(1.62), visibleSize.height / 2));
	this->addChild(btn_right, 5);

	auto btn_left = Button::create("Select_map/arrow_left_ready.png","Select_map/arrow_left.png");
	btn_left->addTouchEventListener(CC_CALLBACK_2(SelectMap::backPage, this));
	btn_left->setAnchorPoint(Vec2(0.5f, 0.5f));
	btn_left->setPosition(Vec2(visibleSize.width / (19.5), visibleSize.height / 2));
	this->addChild(btn_left, 5);

	return true;
}


void SelectMap::nextPage(Ref* sender,ui::Widget::TouchEventType type) {
		_currentPage = (int)_pageView->getCurrentPageIndex();
		_currentPage++;
		_pageView->scrollToPage(_currentPage);
}
void SelectMap::backPage(Ref* sender, ui::Widget::TouchEventType type) {
		_currentPage = (int)_pageView->getCurrentPageIndex();
		_currentPage--;
		_pageView->scrollToPage(_currentPage);
}
cocos2d::Scene * SelectMap::createScene()
{
	return SelectMap::create();
}
void SelectMap::load(Ref* sender, ui::Widget::TouchEventType type) {
	auto scene = TurtorialScene::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(1,scene));
}