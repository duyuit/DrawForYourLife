#include "cocos2d.h"
#include <string>
#include "SonicRunSlowState.h"
#include "SonicData.h"
#include "SonicState.h"
#include "SonicRunNormalState.h"
#include "SonicRunFastState.h"
#include "SonicJumpState.h"
#include "SonicRollState.h"
#include "SonicFallState.h"
#include "SonicHoldState.h"
#include "GameDefine.h"
using namespace cocos2d;
using namespace Define;
#pragma once

class Sonic: public Sprite
{
public:
	Sonic();
	~Sonic();
	void update();
	void handle_swipe(Vec2 start, Vec2 end);
	RefPtr<Animate>  *mCurrentAnimate;
	SonicState *mCurrentState;
	SonicData *mData;
	bool CheckLastFrame();
	void SetStateByTag(SonicState::StateAction action); //Set state by put type of State
	void SetState(SonicState *action);
	void AddLightning();
	bool isLeft = false;
	Vec2 GetVelocity();
	void SetVelocity(int x, int y);
	void SetVelocityX(int x);
private:
	RefPtr<Animate>  *run_slow_Ani;
	RefPtr<Animate>  *run_normal_Ani;
	RefPtr<Animate>  *run_fast_Ani;
	RefPtr<Animate>  *jump_Ani;
	RefPtr<Animate>  *roll_Ani;
	RefPtr<Animate>  *fall_Ani;
	RefPtr<Animate>  *roll_sky_Ani;

	Sprite* lightning=nullptr;
	Sprite* lightning2 = nullptr;


	Action* mCurrentAction;
	Define::SWIPE_DIRECTION cur_Swipe_direction;

	
};

