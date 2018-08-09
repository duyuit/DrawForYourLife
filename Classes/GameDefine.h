#pragma once
#include "cocos2d.h"
#include "../external/tinyxml2/tinyxml2.h"
using namespace std;
using namespace tinyxml2;
using namespace cocos2d;
namespace Define {
	enum SWIPE_DIRECTION
	{
		LEFT,RIGHT,UP,DOWN

	};
	enum TAG
	{
		Player,
		Ring,
		HoldPlace,
		LANDMONSTER,
		land,
		DIELAND,
		MUSHROOM,
		SANDRAT,
		CHEST,
		COCONUT,
		PYRAMID,
		FINISH,
		DRILL,
		BOSS,
		MISSLE
	};
	enum SCENE_NAME
	{
		LV0,
		LV1,
		LV2
	};
	enum SCENE_AREA
	{
		STONE,
		SNOW,
		DESERT

	};
	enum SCENE_LEVELMAP
	{
		MAP_STONE,
		MAP_SNOW,
		MAP_DESERT

	};
	enum BUTTON_TAG
	{
		NONE,
		BUTTON_LEFT,
		BUTTON_RIGHT
	
	};
	enum MUSIC_BG
	{
		TUTORIAL_MUSIC,
		STONE_1_MUSIC,
		STONE_2_MUSIC,
		SNOW_1_MUSIC,
		SNOW_2_MUSIC,
		DESERT_1_MUSIC,
		DESERT_2_MUSIC,
		BOSS_MUSIC
	};

	static float default_sonic_mass = 441;
	static float boss_sonic_mass = 700;

	static int area;
	static int level = 0;
	static string button_left_green_path = "Button/button_left_green.png";
	static string button_right_green_path = "Button/button_right_green.png";
	static string button_left_grey_path = "Button/button_left_grey.png";
	static string button_right_grey_path = "Button/button_right_grey.png";
	static string button_left_blue_path = "Button/button_left_blue.png";
	static string button_right_blue_path = "Button/button_right_blue.png";
	static string button_fail_path = "Button/button_fail.png";
	static string button_left_red_path = "Button/button_left_red.png";
	static string button_right_red_path = "Button/button_right_red.png";

	//Music background
	static int _music_boss_scene_background, _music_menu_scene_background_1, _music_menu_scene_background_2,
		_music_desert_background_1, _music_desert_background_2, _music_snow_background_1, _music_snow_background_2,
		_music_stone_background_1, _music_stone_background_2;
	static char* _music_boss_scene_background_path = "Music/Background/boss_scene_background.mp3";
	static char* _music_menu_scene_background_1_path = "Music/Background/menu_scene_background_1.mp3";
	static char* _music_menu_scene_background_2_path = "Music/Background/menu_scene_background_2.mp3";
	static char* _music_desert_background_1_path = "Music/Background/desert_background_1.mp3";
	static char* _music_desert_background_2_path = "Music/Background/desert_background_2.mp3";
	static char* _music_snow_background_1_path = "Music/Background/snow_background_1.mp3";
	static char* _music_snow_background_2_path = "Music/Background/snow_background_2.mp3";
	static char* _music_stone_background_1_path = "Music/Background/stone_background_1.mp3";
	static char* _music_stone_background_2_path = "Music/Background/stone_background_2.mp3";

	//Music button
	static int _music_btn_arrow_effect, _music_btn_effect_1, _music_btn_effect_2, _music_tap_button_effect;
	static char* _music_btn_arrow_effect_path = "Music/Button/btn_arrow_effect.mp3";
	static char* _music_btn_effect_1_path = "Music/Button/btn_effect_1.mp3";
	static char* _music_btn_effect_2_path = "Music/Button/btn_effect_2.mp3";
	static char* _music_tap_button_effect_path = "Music/Button/tap_button_effect.mp3";

	//Music combo
	static int _music_btn_effect, _music_great_effect, _music_miss_effect, _music_perfect_effect_1, _music_perfect_effect_2, _music_perfect_effect_3;
	static char* _music_btn_effect_path = "Music/Combo/btn_effect.mp3";
	static char* _music_great_effect_path = "Music/Combo/great_effect.mp3";
	static char* _music_miss_effect_path = "Music/Combo/miss_effect.mp3";
	static char* _music_perfect_effect_1_path = "Music/Combo/perfect_effect_1.mp3";
	static char* _music_perfect_effect_2_path = "Music/Combo/perfect_effect_2.mp3";
	static char* _music_perfect_effect_3_path = "Music/Combo/perfect_effect_3.mp3";

	//Music object
	static int _music_drop_ring_effect, _music_eat_ring_effect, _music_mushroom_effect;
	static char* _music_drop_ring_effect_path = "Music/Object/drop_ring_effect.mp3";
	static char* _music_eat_ring_effect_path = "Music/Object/eat_ring_effect.mp3";
	static char* _music_mushroom_effect_path = "Music/Object/mushroom_effect.mp3";

	//Music sonic
	static int _music_sonic_jump_effect, _music_sonic_roll_effect;
	static char* _music_sonic_jump_effect_path = "Music/Sonic/sonic_jump_effect.mp3";
	static char* _music_sonic_roll_effect_path = "Music/Sonic/sonic_roll_effect.mp3";

	//Music table
	static int _music_boss_finish_effect, _music_finish_level_effect, _music_game_over_effect_1, _music_game_over_effect_2;
	static char* _music_boss_finish_effect_path = "Music/Table/boss_finish_effect.mp3";
	static char* _music_finish_level_effect_path = "Music/Table/finish_level_effect.mp3";
	static char* _music_game_over_effect_1_path = "Music/Table/game_over_effect_1.mp3";
	static char* _music_game_over_effect_2_path = "Music/Table/game_over_effect_2.mp3";

	//Music voice
	static int _music_voice_combo, _music_voice_end_lose, _music_voice_end_win, _music_voice_miss, _music_voice_start_1, _music_voice_start_2;
	static char* _music_voice_combo_path = "Music/Voice/voice_combo.mp3";
	static char* _music_voice_end_lose_path = "Music/Voice/voice_end_lose.mp3";
	static char* _music_voice_end_win_path = "Music/Voice/voice_end_win.mp3";
	static char* _music_voice_miss_path = "Music/Voice/voice_miss.mp3";
	static char* _music_voice_start_1_path = "Music/Voice/voice_start_21.mp3";
	static char* _music_voice_start_2_path = "Music/Voice/voice_start_1.mp3";

	static float randomValueBetween(float min, float max)
	{
		assert(max > min);
		float random = ((float)rand()) / (float)RAND_MAX;

		// generate (in your case) a float between 0 and (4.5-.78)
		// then add .78, giving you a float between .78 and 4.5
		float range = max - min;
		return (random*range) + min;
	}

	static Vector<SpriteFrame*> loadAnim(std::string path, std::string key)
	{
		Vector<SpriteFrame*> list;
		std::string path2 = FileUtils::getInstance()->getStringFromFile(path);

		tinyxml2::XMLDocument *doc = new tinyxml2::XMLDocument();
		tinyxml2::XMLError eResult = doc->Parse(path2.c_str(), path2.size());

		tinyxml2::XMLElement* root = doc->RootElement();
		tinyxml2::XMLElement* child = root->FirstChildElement();
		while (child)
		{
			if (child->Attribute("name") == key)
			{
				tinyxml2::XMLElement* ele = child->FirstChildElement();
				while (ele)
				{
					float x;
					ele->QueryFloatAttribute("x", &x);
					float y;
					ele->QueryFloatAttribute("y", &y);
					float w;
					ele->QueryFloatAttribute("w", &w);
					float h;
					ele->QueryFloatAttribute("h", &h);


					list.pushBack(SpriteFrame::create(child->Attribute("imagePath"), Rect(x, y, w, h)));

					ele = ele->NextSiblingElement();
				}
				break;
			}
			child = child->NextSiblingElement();
		}
	
		delete doc;

		return list;
	}


}

