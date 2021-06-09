#pragma once

#ifndef _Hero_H_
#define _Hero_H_
#include "Role.h"
//#include "Item/Weapon.h"
#include "Const/Const.h"
//#include "Item/Weapon.h"

static float gHeroSpeed = 150.;
static int gHeroDamage = 5;

class Hero : public Role
{
public:
	Sprite* pHero;
	static Hero* createHero(cocos2d::Point position);
	void heroInit(cocos2d::Point position);

	Animate* actionStand();

	virtual bool init() override;
	CREATE_FUNC(Hero);


	void move(int face, const char* pAnimateName,
		int width = 50, int heigh = 100, int frames = 4);


	bool isKeyPressed(EventKeyboard::KeyCode keyCode);
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);
	void keyPressedDuration(EventKeyboard::KeyCode code);


	void update(float dt = 0.4f);
	int m_nowFacing;

	std::map<cocos2d::EventKeyboard::KeyCode, bool> m_keys;

protected:
	
};

#endif//!_CHARACTER_H_