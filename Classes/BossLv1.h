#pragma once
#include "BossDrill.h"
#include "BossPlane.h"
#include "MultipleButton.h"
#include "TapButton.h"
class BossLv1:public Node
{
public:
	enum STATE
	{
		IDLE,
		RUN,
		RUNBACK,
		FIGHT,
		GETBACKDRILL,

	};
	void GenerateButton();
	void GenerateMultiButton();
	BossLv1(Vec2 pos,Sonic* sonic, Layer* layer);
	~BossLv1();
	int hp =15;
	bool isAlmostBroke = false;
	bool isLeft = false;
	bool isDelete = false;
	BossDrill* drill;
	BossPlane* plane;
	Sonic* _mSonic;
	int count_to_change_state = 0;

	ProgressTimer *mouseBar;
	void GetDame();

	bool isCrazy = false;
	bool isSonicAttack = false;

	void ResetButton();
	void Broke();
	STATE currentState = IDLE;
	TapButton* currentButton = nullptr;
	MultipleButton* current_multiButton = nullptr;

	void ReturnPlane();
	void AddPercent(TYPE_SCORE score);
	int maximum_hit=0;
	void SetState(STATE state);
	void updateStart(float dt);
	void update(float dt);
	void Merge();
	void Flip();
};

