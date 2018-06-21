#include "cocos2d.h"
#include <string>
#include "tinyxml2\tinyxml2.h"
#include "SonicRunSlowState.h"
#include "SonicData.h"
#include "SonicState.h"
#include "SonicRunNormalState.h"
#include "SonicRunFastState.h"
#include "SonicJumpState.h"
#include "SonicRollState.h"
#include "GameDefine.h"
using namespace cocos2d;
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
	static Vector<SpriteFrame*> loadAnim(char* path, std::string key);
	void SetStateByTag(SonicState::StateAction action); //Set state by put type of State
	void SetState(SonicState *action);
	bool isLeft = false;
	Vec2 velocity=Vec2(0, 0);
private:
	RefPtr<Animate>  *run_slow_Ani;
	RefPtr<Animate>  *run_normal_Ani;
	RefPtr<Animate>  *run_fast_Ani;
	RefPtr<Animate>  *jump_Ani;
	RefPtr<Animate>  *roll_Ani;
	Action* mCurrentAction;
	Define::SWIPE_DIRECTION cur_Swipe_direction;

	
};

