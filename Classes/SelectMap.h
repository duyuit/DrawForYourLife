#pragma once
#ifndef __SelectMap__
#define __SelectMap__
#include "cocos2d.h"
#include "ui\CocosGUI.h"
#include "TurtorialScene.h"
#include "LevelMap.h"
using namespace std;
using namespace cocos2d;
using namespace cocos2d::ui;
class SelectMap : public cocos2d::Scene
{
public:
	SelectMap();
	~SelectMap();
	Button* _btn_map_1;
	Button* _btn_map_2;
	Button* _btn_map_3;
	PageView* _pageView;
	int _currentPage;

	virtual bool init();
	void nextPage(Ref* sender, ui::Widget::TouchEventType type);
	void backPage(Ref* sender, ui::Widget::TouchEventType type);
	void load(Ref* sender, ui::Widget::TouchEventType type);
	static cocos2d::Scene* createScene();
	CREATE_FUNC(SelectMap);
};
#endif 
