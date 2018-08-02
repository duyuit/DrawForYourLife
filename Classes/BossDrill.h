#pragma once
#include "GameDefine.h"
#include "GameParticle.h"
class BossDrill:public Node
{
public:
	BossDrill();
	~BossDrill();
	int count_to_generate_dust = 0;

	bool isLeft = false;
	Sprite* back_car,*front_car;
	Sprite* drill;
	Sprite* chain1, *chain2, *chain3;
	RefPtr<Animate>  *drill_anim;
	RefPtr<Animate>  *car_anim;
	void update(float dt);
	Node* parent = nullptr;

	void AlmostBreak();
	void Break();

	//void GenerateDust();
	void Flip(bool isFlip);
	void ActiveDrill();
	void FireDrill();
	void ReturnDrill();
};

