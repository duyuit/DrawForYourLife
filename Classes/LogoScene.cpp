#include "LogoScene.h"
USING_NS_CC;
using namespace std;
using namespace ui;


LogoScene::LogoScene()
{
}


LogoScene::~LogoScene()
{
}

void LogoScene::LoadSound()
{
	audio->preloadBackgroundMusic(Define::_music_lv1_background_path);
	
	audio->preloadEffect(Define::_music_combo_effect_path);
	audio->preloadEffect(Define::_music_eat_ring_efftect_path);
	audio->preloadEffect(Define::_music_roll_effect_path);
	audio->preloadEffect(Define::_music_jump_effect_path);
	audio->preloadEffect(Define::_music_button_effect_path);
	audio->preloadEffect(Define::_music_finish_level_path);

	audio->preloadBackgroundMusic(Define::_music_stone_background_1_path);
	audio->preloadBackgroundMusic(Define::_music_stone_background_2_path);

	audio->preloadBackgroundMusic(Define::_music_snow_background_1_path);
	audio->preloadBackgroundMusic(Define::_music_snow_background_2_path);

	audio->preloadBackgroundMusic(Define::_music_desert_background_1_path);
	audio->preloadBackgroundMusic(Define::_music_desert_background_2_path);

	audio->preloadBackgroundMusic(Define::_music_boss_scene_background_path);
	audio->preloadBackgroundMusic(Define::_music_menu_scene_background_1_path);
	audio->preloadBackgroundMusic(Define::_music_menu_scene_background_2_path);

	audio->preloadEffect(Define::_music_btn_arrow_effect_path);
	audio->preloadEffect(Define::_music_btn_effect_1_path);
	audio->preloadEffect(Define::_music_btn_effect_2_path);

	audio->preloadEffect(Define::_music_drop_ring_effect_path);
	audio->preloadEffect(Define::_music_game_over_effect_path);
	audio->preloadEffect(Define::_music_boss_finish_effect_path);

	audio->playBackgroundMusic(Define::_music_menu_scene_background_1_path);
}


cocos2d::Scene * LogoScene::createScene()
{
	return LogoScene::create();
}

bool LogoScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto background = Sprite::create("Menu/logo.jpg");
	background->setScale(visibleSize.width / (background->getContentSize().width), visibleSize.height / (background->getContentSize().height));
	background->setAnchorPoint(Vec2(0.5, 0.5));
	background->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(background);

	auto actionMoveDone = CallFuncN::create(CC_CALLBACK_1(LogoScene::nextScene, this));
	this->runAction(Sequence::create(DelayTime::create(2.0f), actionMoveDone, NULL));

	LoadSound();
	return true;
}
void LogoScene::nextScene(cocos2d::Node* sender)
{
	auto sceneMeunu = MenuScene::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(1, sceneMeunu));
}