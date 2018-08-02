#include "cocos2d.h"
#include <string>
#include "SonicData.h"
#include "SonicState.h"
#include "SonicRunFastState.h"
#include "SonicJumpState.h"
#include "SonicRollState.h"
#include "SonicFallState.h"
#include "SonicHoldState.h"
#include "SonicHurtState.h"
#include "SonicDieState.h"
#include "SonicRunSkipState.h"
#include "SonicRollChestState.h"
#include "SonicStopState.h"
#include "SonicCounterState.h"
#include "SonicEndState.h"
#include "SonicRollSky.h"
#include "GameDefine.h"
#include "GameParticle.h"
#include "SmallRing.h"
#include "Mushroom.h"
#include <SimpleAudioEngine.h>
#include <AudioEngine.h>
using namespace CocosDenshion;

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
	bool isInMultipleButton = false;
	bool scene_over = false;

	bool CheckLastFrame(); // Check current animate is last Frame?
	void SetStateByTag(SonicState::StateAction action); //Set state by put type of State
	void SetState(SonicState *action); //Set state by new State()

	bool isFinish = false;
	bool isLeft = false;   // Check Direction Sonic
	Vec2 GetVelocity(); 
	void HandleCollision(Sprite *sprite); //Use to handle collision with objects
	void SetVelocity(int x, int y); 
	void SetVelocityX(int x); //Set velocity X, old Y

	Node* mCurrentButton = nullptr;
	bool isDelete = false;
	void DropRing();

	int ringCollected = 0; //Count rings Sonic collected
	int countCombo = 0; //Count the combo tap button, no missing
	int maxCombo = 0; //Count max combo
	int countPerfect = 0;
	int countGreat = 0;
	int countBad = 0;
	int score = 0;
	float scoreMul = 1.0; //Multiple the score
	bool isRed = false;
	bool isGameOver = false;

	void SwapAni(RefPtr<Animate> *&blue, RefPtr<Animate> *&red); //Swap red and blue Sonic
	void SwapAllAni();
	void DisableCurrentButton();
	void ActiveButton(BUTTON_TAG dir);
	BUTTON_TAG mJustTap = NONE;


	Sprite* _roll_circle = nullptr;
	Sprite* _roll_effect = nullptr;
	Sprite* _transform_red = nullptr;
	Sprite* _transform_blue = nullptr;
	RefPtr<Animate>* _transform_red_Ani = nullptr;
	RefPtr<Animate>* _transform_blue_Ani = nullptr;

private:

	RefPtr<Animate>  *run_fast_Ani;
	RefPtr<Animate>  *jump_Ani;
	RefPtr<Animate>  *roll_Ani;
	RefPtr<Animate>  *fall_Ani;
	RefPtr<Animate>  *roll_sky_Ani;
	RefPtr<Animate>  *hurt_Ani;
	RefPtr<Animate>  *run_skip_Ani;
	RefPtr<Animate>  *roll_chest_Ani;
	RefPtr<Animate>  *stop_Ani;
	RefPtr<Animate>  *counter_Ani;
	RefPtr<Animate>  *end_Ani;


	RefPtr<Animate>  *run_fast_red_Ani;
	RefPtr<Animate>  *jump_red_Ani;
	RefPtr<Animate>  *roll_red_Ani;
	RefPtr<Animate>  *fall_red_Ani;
	RefPtr<Animate>  *roll_sky_red_Ani;
	RefPtr<Animate>  *hurt_red_Ani;
	RefPtr<Animate>  *run_skip_red_Ani;
	RefPtr<Animate>  *roll_chest_red_Ani;
	RefPtr<Animate>  *stop_red_Ani;
	RefPtr<Animate>  *counter_red_Ani;
	RefPtr<Animate>  *end_red_Ani;

	Sprite* dust = nullptr;
	Sprite* flame = nullptr;
	MotionStreak* streak = nullptr;

	void updateStart(float dt);
	Action* mCurrentAction;
	Define::SWIPE_DIRECTION cur_Swipe_direction;

	Vector<SpriteFrame*>  sonic_loadAnim(bool isRed, std::string key);
	



	
};

