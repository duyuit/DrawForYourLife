#pragma once
#include "cocos2d.h"
#include "Sonic.h"
#include "ui/CocosGUI.h"

using namespace cocos2d;
using namespace ui;

#define MAX(a,b) ((a) > (b) ? (a) : (b))

class RingComboScore : public Layer
{
public:

	Sonic* _mySonic;
	int _pre_combo = 0;
	int _prev_score = 0;
	int _delta_score = 0; //Calculate plus score
	bool isCool = false, isGood = false, isExcellent = false, isPerfect = false;

	Sprite* _ringIcon;
	Label* _countRing;

	Label *_xCombo, *_xCombo2;
	Label* _evaluate; //Label (Nice!, Good!, Excellent!, Perfect!)

	Label* _score;
	Label* _plusScore;
	int _distance, _distance2 = 0;

	Sprite* flame;
	RingComboScore(Sonic* mSonic);

	void UpdateCombo();
	void ResetCombo();

	void SetColor();
	void SetLabel();

	void CreateEffect();
	void Evaluate();

	void update(float dt);
private:
	RefPtr<Animate>  *flame_Ani;
	RefPtr<Animate>  *flame_blue_Ani;
	Vector<SpriteFrame*> flame_FL;
};

