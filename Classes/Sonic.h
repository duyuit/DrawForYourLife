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
#include "SonicHurtState.h"
#include "GameDefine.h"
#include "GameParticle.h"
#include "SmallRing.h"
#include "Mushroom.h"
using namespace cocos2d;
using namespace Define;
#pragma once

class Sonic: public Sprite
{
public:
	Sonic();
	~Sonic();
	void update(float dt);
	void handle_swipe(Vec2 start, Vec2 end);
	RefPtr<Animate>  *mCurrentAnimate;
	SonicState *mCurrentState;
	SonicData *mData;
	bool CheckLastFrame(); // Check current animate is last Frame?
	void SetStateByTag(SonicState::StateAction action); //Set state by put type of State
	void SetState(SonicState *action); //Set state by new State()

	bool isLeft = false;   // Check Direction Sonic
	Vec2 GetVelocity(); 
	void HandleCollision(Sprite *sprite); //Use to handle collision with object
	void SetVelocity(int x, int y); 
	void SetVelocityX(int x); //Set velocity X, old Y

	void DropRing();
	int ringCollected = 0; //Count rings Sonic collected
	int baseLife = 2; //Count the number of your dropping rings (drop ring 3 times you die)
	int countCombo = 0; //Count the combo tap button, no missing
	bool isBlueToRed = false, isRedToBlue = false;

	void SwapAni(RefPtr<Animate> *&blue, RefPtr<Animate> *&red); //Swap red and blue Sonic
	void SwapAllAni();

	std::vector<int> _list_just_tap;
	BUTTON_TAG mJustTap = NONE;


	Sprite* _roll_circle = nullptr;
	Sprite* _roll_effect = nullptr;
private:
	RefPtr<Animate>  *run_slow_Ani;
	RefPtr<Animate>  *run_normal_Ani;
	RefPtr<Animate>  *run_fast_Ani;
	RefPtr<Animate>  *jump_Ani;
	RefPtr<Animate>  *roll_Ani;
	RefPtr<Animate>  *fall_Ani;
	RefPtr<Animate>  *roll_sky_Ani;
	RefPtr<Animate>  *hurt_Ani;

	RefPtr<Animate>  *run_slow_red_Ani;
	RefPtr<Animate>  *run_normal_red_Ani;
	RefPtr<Animate>  *run_fast_red_Ani;
	RefPtr<Animate>  *jump_red_Ani;
	RefPtr<Animate>  *roll_red_Ani;
	RefPtr<Animate>  *fall_red_Ani;
	RefPtr<Animate>  *roll_sky_red_Ani;
	RefPtr<Animate>  *hurt_red_Ani;


	Sprite* dust = nullptr;
	Sprite* flame = nullptr;
	MotionStreak* streak = nullptr;

	void updateStart(float dt);
	Action* mCurrentAction;
	Define::SWIPE_DIRECTION cur_Swipe_direction;



	
};

