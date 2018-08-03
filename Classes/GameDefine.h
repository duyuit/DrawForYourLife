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
		CHEST,
		COCONUT,
		FINISH,
		DRILL,
		BOSS
	};
	enum SCENE_NAME
	{
		LV0,
		LV1
	};
	enum SCENE_AREA
	{
		STONE,
		SNOW,
		DESERT

	};
	enum BUTTON_TAG
	{
		NONE,
		BUTTON_LEFT,
		BUTTON_RIGHT
	
	};
	static float default_sonic_mass = 441;
	static float boss_sonic_mass = 700;

	static string button_left_green_path = "Button/button_left_green.png";
	static string button_right_green_path = "Button/button_right_green.png";
	static string button_left_grey_path = "Button/button_left_grey.png";
	static string button_right_grey_path = "Button/button_right_grey.png";
	static string button_left_blue_path = "Button/button_left_blue.png";
	static string button_right_blue_path = "Button/button_right_blue.png";
	static string button_fail_path = "Button/button_fail.png";

	static char* _music_lv1_background_path = "Music/lv1_background.mp3";
	static char* _music_roll_effect_path= "Music/roll_effect.wav";
	static char* _music_eat_ring_efftect_path = "Music/eat_ring_effect.wav";
	static char* _music_jump_effect_path = "Music/sonic_jump_effect.mp3";
	static char* _music_combo_effect_path = "Music/combo_effect.mp3";
	static char* _music_button_effect_path = "Music/select_button.mp3";
	static char* _music_finish_level_path = "Music/finish_level_background.mp3";

	static char* _music_stone_background_1_path = "Music/new/stone_background_1.mp3";
	static char* _music_stone_background_2_path = "Music/new/stone_background_2.mp3";

	static char* _music_snow_background_1_path = "Music/new/snow_background_1.mp3";
	static char* _music_snow_background_2_path = "Music/new/snow_background_2.mp3";

	static char* _music_desert_background_1_path = "Music/new/desert_background_1.mp3";
	static char* _music_desert_background_2_path = "Music/new/desert_background_2.mp3";

	static char* _music_boss_scene_background_path = "Music/new/boss_scene_background.mp3";
	static char* _music_menu_scene_background_1_path = "Music/new/menu_scene_background_1.mp3";
	static char* _music_menu_scene_background_2_path = "Music/new/menu_scene_background_2.mp3";

	static char* _music_btn_arrow_effect_path = "Music/new/btn_arrow_effect.mp3";
	static char* _music_btn_effect_1_path = "Music/new/btn_effect_1.mp3";
	static char* _music_btn_effect_2_path = "Music/new/btn_effect_2.mp3";

	static char* _music_drop_ring_effect_path = "Music/new/drop_ring_effect.mp3";
	static char* _music_game_over_effect_path = "Music/new/game_over_effect.mp3";
	static char* _music_boss_finish_effect_path = "Music/new/boss_finish_effect.mp3";

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

		return list;
	}

}

