#pragma once
#include "cocos2d.h"
#include "Sonic.h"
#include "ui/CocosGUI.h"
using namespace cocos2d;
using namespace ui;

class ComboScore : public Layer
{
public:
	ComboScore() {};

	Sprite* _sprite;
	Sonic* _mySonic;
	Label* _label;	//Label X combo
	Label* _label2; //Label (Nice!, Good!, Excellent!, Perfect!)

	void update(float dt) 
	{
		SetColor();
	}

	ComboScore(Sonic* mSonic) {
		_mySonic = mSonic;

		//_sprite = Sprite::create("label-ring-bg.png");
		//_sprite->setAnchorPoint(Vec2(0.5f, 0.5f));
		//_sprite->setVisible(false);
		//this->addChild(_sprite, 1);

		_label = Label::createWithTTF("", "fonts/PixelGameFont.ttf", 24);
		_label->setAnchorPoint(Vec2(0.5f, 0.5f));
		_label->setVisible(false);
		this->addChild(_label, 1);	

		_label2 = Label::createWithTTF("", "fonts/INVASION2000.ttf", 48);
		_label2->setAnchorPoint(Vec2(0.5f, 0.5f));
		_label2->setVisible(false);
		_mySonic->addChild(_label2, 100);

		this->scheduleUpdate();
	}

	void SetColor();
	void UpdateCombo();
	void ResetCombo();
	void CreateEffect();	
	void Evaluate();

};

