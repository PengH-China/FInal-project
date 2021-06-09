#pragma once
#ifndef _SOLDIER_H_
#define _SOLDIER_H_
#include "cocos2d.h"
#include "const/Const.h"
USING_NS_CC;

class Soldier :public Layer
{
public:
	Sprite* soldier;
	static Soldier* createSoldier(cocos2d::Point position);
	void soldierInit(cocos2d::Point position);

	//站立时动作
	Animate* actionStand();


	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(Soldier);


	void move(int face, const char* pAnimateName,
		int width = 50, int heigh = 100, int frames = 4);


	bool isKeyPressed(EventKeyboard::KeyCode keyCode);
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);
	void keyPressedDuration(EventKeyboard::KeyCode code);



	void update(float dt = 0.4f);
	int m_nowFacing;

	std::map<cocos2d::EventKeyboard::KeyCode, bool> m_keys;
};

#endif//// !_Soldier_H__