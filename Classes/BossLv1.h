#pragma once
#include "BossDrill.h"
#include "BossPlane.h"
class BossLv1
{
public:
	BossLv1(Vec2 pos, Layer* layer);
	~BossLv1();

	BossDrill* drill;
	BossPlane* plane;
	void updateStart(float dt);
	void Merge();
};

