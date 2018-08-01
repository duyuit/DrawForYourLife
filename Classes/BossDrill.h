#pragma once
#include "GameDefine.h"
class BossDrill:public Node
{
public:
	BossDrill();
	~BossDrill();
	int count_to_generate_dust = 0;

	Sprite* back_car,*front_car;
	Sprite* drill;
	Sprite* chain1, *chain2, *chain3;
	RefPtr<Animate>  *drill_anim;
	RefPtr<Animate>  *car_anim;
	void update(float dt);
	void GenerateDust();
	void Flip(bool isFlip);
	void ActiveDrill();
	void FireDrill();
	void ReturnDrill();
};

