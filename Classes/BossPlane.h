#pragma once
#include "GameDefine.h"
class BossPlane:public Node
{
public:
	BossPlane();
	~BossPlane();

	Sprite* front;
	Sprite* back;
	Sprite* face;
	Sprite* wing;

	RefPtr<Animate>  *back_anim;
	RefPtr<Animate>  *normal_face;
	RefPtr<Animate>  *angry_face;
	RefPtr<Animate>  *die_face;

	RefPtr<Animate>  *turn_off_wing;
	RefPtr<Animate>  *turn_on_wing;
	RefPtr<Animate>  *normal_wing;

	void ActiveWing(bool on_off);
	void update(float dt);
	int count_to_roll_wing = 0;
	bool isOn = true;
	void Angry();
	void Break();
	void Fire();
	void Flip(bool isFlip);
};

