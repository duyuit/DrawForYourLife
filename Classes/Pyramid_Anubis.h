#pragma once
#include "GameDefine.h"
#include "AnubisMonster.h"
class Pyramid_Anubis : public Sprite
{
public:
	Pyramid_Anubis();
	~Pyramid_Anubis();
	Sprite* _pyramid;
	void ComeBack();
};

