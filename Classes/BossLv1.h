#pragma once
#include "BossDrill.h"
#include "BossPlane.h"

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
	BossLv1(Vec2 pos,Sonic* sonic, Layer* layer);
	~BossLv1();

	bool isLeft = false;
	BossDrill* drill;
	BossPlane* plane;
	Sonic* _mSonic;
	int count_to_change_state = 0;

	STATE currentState = IDLE;
	TapButton* currentButton = nullptr;
	int maximum_hit=0;
	void SetState(STATE state);
	void updateStart(float dt);
	void update(float dt);
	void Merge();
	void Flip();
};

