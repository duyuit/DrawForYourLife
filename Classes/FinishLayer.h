#pragma once

#include "cocos2d.h"
#include "Sonic.h"


class FinishLayer : public cocos2d::Layer
{
public:
	FinishLayer(Sonic* mySonic, Layer* cur_scene, SCENE_LEVELMAP currentLevelMap);
	~FinishLayer();
	//Start Count
	int countPerfect = 0;
	int countGreat = 0;
	int countBad = 0;
	int score = 0;
	int total = 0;
	int maxCombo = 0;
	int bonus = 0;
	int ring = 0;
	int numStar = 0;
	Sprite* star1;
	Sprite* star2;
	Sprite* star3;
	SCENE_LEVELMAP levelMap;
	LayerColor *layer = nullptr;
	Layer *current_scene = nullptr;
	SCENE_NAME current_level;
	SCENE_LEVELMAP current_area;
	Sonic* mySonic;

	Sprite* boardScore;
	Sprite* _bar;
	Label* _result;

	Label* _labelRing;
	Label* _labelRingNum;

	Label* _labelPerfect;
	Label* _labelPerfectNum;
	string font = "fonts/hemi.ttf";


	Label* _labelBestcombo;
	Label* _labelBestcomboNum;


	Label* _labelBonus;
	Label* _labelBonusNum;

	Label* _labelScore;
	Label* _labelScoreNum;

	Label* _labelTotal;
	Label* _labelTotalNum;



	int per = -1;
	int bestCombo = -1;
	int bad = -1;
	int scoreCount = -1;
	int totalCount = -1;
	int ringCount = -1;
	int bonusCount = -1;
	bool isJumpPoint;
	//End Count
	void update(float dt);

};
