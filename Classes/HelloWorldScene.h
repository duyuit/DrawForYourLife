/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "MyUI.h"
#include "SmallRing.h"
#include "GameParticle.h"
#include "LandMonster.h"
#include "InfiniteParallaxNode.h"
#include "TapButton.h"

using namespace ui;
class HelloWorld : public cocos2d::Layer
{
public:

	Vec2 start_touch_position, end_touch_position;
	Sonic* mSonic;
	Vector<TapButton*> listButton;
	InfiniteParallaxNode* _backgroundNode;
	InfiniteParallaxNode* _backgroundNode2;


	CCTMXTiledMap * _tileMap;
	void LoadMap();
	void setViewPointCenter(Point position);
	bool onContactBegin(cocos2d::PhysicsContact & contact);
	void update(float dt);
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
	void updateStart(float dt);
    // implement the "static create()" method manually
	virtual bool init();
	static cocos2d::Scene* createScene();
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
