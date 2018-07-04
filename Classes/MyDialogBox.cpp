#include "MyDialogBox.h"



MyDialogBox::MyDialogBox()
{
	_box = Sprite::create("GameComponents/dialog_box.png");
	_box->setAnchorPoint(Vec2(0, 0));

	_text= Label::createWithTTF("", "fonts/PixelGameFont.ttf", 35);
	
	_text->setAnchorPoint(Vec2(0, 0));
	_text->setTextColor(Color4B(0, 0, 0, 255));


	_tap = Label::createWithTTF("(Tap to continue!)","fonts/PixelGameFont.ttf",30);
	_tap->setTextColor(Color4B(0, 0, 0, 255));
	_tap->setAnchorPoint(Vec2(0, 0));
	
	UpdatePosition();

	_myText = "Welcome to Sonic's World.\nLet's start the game!!";
	this->setAnchorPoint(Vec2(0, 0));

	auto kk=_tap->getAnchorPoint();
	//_text->setPosition(50, 50);
	this->addChild(_box,0);
	this->addChild(_text,1);
	this->addChild(_tap, 1);
	this->scheduleUpdate();
}


MyDialogBox::~MyDialogBox()
{
}

void MyDialogBox::UpdatePosition()
{
	
}

void MyDialogBox::SetScale(float dt)
{
	this->setScale(dt);
	_tap->setPosition(_box->getContentSize().width*dt - _tap->getContentSize().width,0);

	Size newSize = _box->getContentSize()*dt;
	_text->setPosition(newSize.width/3,newSize.height / 2);
	_tap->setPosition(newSize.width, _tap->getContentSize().height*dt);
}

void MyDialogBox::SetTapToContinue(bool is)
{
	if (is)
	{
		auto fadeOut = FadeOut::create(0.1f);
		auto reverse = fadeOut->reverse();
		ActionInterval *fade = Sequence::create(fadeOut, reverse, nullptr);
		auto fading = RepeatForever::create(fade);
		_tap->runAction(fading);
	}
	else _tap->stopAllActions();
}

void MyDialogBox::UpdateString(std::string text)
{
	if (text.size() > 30)
		_text->setBMFontSize(30);
	_myText = text;
	_current_position_text = 0;
	_delay_text = 0;
	_text->setString("");

}

void MyDialogBox::update(float dt)
{
	if (_current_position_text < _myText.size())
	{
		_delay_text++;
		if (_delay_text == 2)
		{
			_delay_text = 0;
			_text->setString(_text->getString() + _myText.at(_current_position_text));
			_current_position_text++;
		}
	}
	
}
