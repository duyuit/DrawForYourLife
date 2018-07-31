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
	Sprite* _btn_map_1;
	Sprite* _btn_map_2;
	Sprite* _btn_map_3;
	Button* _btn_map;
	Button* btn_right;
	Button* btn_left;
	PageView* _pageView;
	int _currentPage;
	string font = "fonts/hemi.ttf";

	virtual bool init();
	void nextPage(Ref* sender, ui::Widget::TouchEventType type);
	void backPage(Ref* sender, ui::Widget::TouchEventType type);
	void load(Ref* sender, ui::Widget::TouchEventType type);
	void update(float dt);
	static cocos2d::Scene* createScene();
	CREATE_FUNC(SelectMap);
};
#endif 
