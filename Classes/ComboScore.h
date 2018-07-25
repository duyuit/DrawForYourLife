#pragma once
#include "cocos2d.h"
#include "Sonic.h"
#include "ui/CocosGUI.h"
using namespace cocos2d;
using namespace ui;

class ComboScore : public Layer
{
public:
	//Sprite* _sprite;
	Sonic* _mySonic;
	int _pre_combo = 0;
	bool isCool = false, isGood = false, isExcellent = false, isPerfect = false;
	Label* _label;	//Label X combo
	Label* _label2; //Label (Nice!, Good!, Excellent!, Perfect!)
	int _distance = 0;

	Sprite* flame;
	ComboScore(Sonic* mSonic);

	void SetColor();
	void UpdateCombo();
	void ResetCombo();
	void CreateEffect();	
	void Evaluate();

	void update(float dt);
private:
	RefPtr<Animate>  *flame_Ani;
	RefPtr<Animate>  *flame_blue_Ani;
	Vector<SpriteFrame*> flame_FL;
};

