
#pragma once
#include "cocos2d.h"
#include "GameDefine.h"
using namespace cocos2d;
enum MONSTERSTATE
{
	IDLE,
	RUN,
	DIE,
	FIGHT
};
class Monster:public Sprite
{
public:
	Monster();

	bool _isLeft = false;
	int _time_action = 0;
	RefPtr<Animate>  *_currentAnimate;
	MONSTERSTATE _currentState;
	Action* _currentAction;
	void HandleCollision(Sprite *sprite); //Use to handle collision with object
	void update(float dt);
	void SetStateByTag(MONSTERSTATE state);
	~Monster();
protected:
	RefPtr<Animate>  *_runAni;
	RefPtr<Animate>  *_idleAni;
	RefPtr<Animate>  *_fightAni;
	RefPtr<Animate>  *_dieAni;
	
};

