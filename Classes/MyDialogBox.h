#pragma once
#include "cocos2d.h"
using namespace cocos2d;

class MyDialogBox : public Node
{
public:
	MyDialogBox();
	~MyDialogBox();
	Sprite* _box;
	Label* _text;
	Label* _tap;
	int _delay_text = 0;
	int _current_position_text = 0;
	std::string _myText="";


	void UpdatePosition();
	void SetScale(float dt);
	void SetTapToContinue(bool is);
	void UpdateString(std::string text);
	void update(float dt);

};

