
#pragma once
#include "cocos2d.h"
#include "GameDefine.h"
#include "TapButton.h"
#include "MultipleButton.h"
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
	void Init(Sonic* sonic);
	bool _isLeft = false;
	int _time_action = 0;
	RefPtr<Animate>  *_currentAnimate;
	MONSTERSTATE _currentState;
	Action* _currentAction;
	TapButton *_tapButton;
	Sonic* _mSonic;
	MultipleButton* _multiButton;

	bool CheckLastFrame();
	bool isDelete = false;
	virtual void HandleCollision(Sprite *sprite); //Use to handle collision with object
	virtual void update(float dt);
	virtual void SetStateByTag(MONSTERSTATE state);
	~Monster();
protected:
	RefPtr<Animate>  *_runAni;
	RefPtr<Animate>  *_idleAni;
	RefPtr<Animate>  *_fightAni;
	RefPtr<Animate>  *_dieAni;
	
};

