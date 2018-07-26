#pragma once
#include "cocos2d.h"
#include "GameDefine.h"

class FinishFlag :public Sprite
{
public:
	FinishFlag();
	~FinishFlag();
	RefPtr<Animate>  *end;
	void RunAnimation();
};

