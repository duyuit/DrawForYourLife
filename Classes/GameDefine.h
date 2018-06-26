#pragma once
#include "cocos2d.h"
#include "tinyxml2\tinyxml2.h"
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
		land_monster,
		land
	};
	static float randomValueBetween(float min, float max)
	{
		assert(max > min);
		float random = ((float)rand()) / (float)RAND_MAX;

		// generate (in your case) a float between 0 and (4.5-.78)
		// then add .78, giving you a float between .78 and 4.5
		float range = max - min;
		return (random*range) + min;
	}
	static Vector<SpriteFrame*> loadAnim(char* path, std::string key)
	{
		Vector<SpriteFrame*> list;

		tinyxml2::XMLDocument xml_doc;
		tinyxml2::XMLError eResult = xml_doc.LoadFile(path);

		tinyxml2::XMLElement* root = xml_doc.RootElement();
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
