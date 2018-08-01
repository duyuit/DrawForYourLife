#pragma once
#include "GameDefine.h"
class BossDrill:public Node
{
public:
	BossDrill();
	~BossDrill();

	Sprite* car;
	Sprite* drill;

	RefPtr<Animate>  *drill_anim;
	RefPtr<Animate>  *car_anim;

	void ActiveDrill();
};

