#pragma once
#include "BossDrill.h"
#include "BossPlane.h"
class BossLv1:public Node
{
public:
	BossLv1(Vec2 pos, Layer* layer);
	~BossLv1();
	bool isLeft = false;
	BossDrill* drill;
	BossPlane* plane;
	int count_to_change_state = 0;

	enum STATE
	{
		IDLE,
		RUN,
		FIGHT,
	};
	void SetState(STATE state);
	void updateStart(float dt);
	void update(float dt);
	void Merge();
	void Flip();
};

