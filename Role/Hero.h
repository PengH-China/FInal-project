/**
*@file Hero.cpp
*@author 张子涵(Zhang Zihan),蔡明宏,彭浩
*@time 2021-06-11
*/

#pragma once
#ifndef _HERO_H_
#define _HERO_H_
#include "cocos2d.h"
#include "Role.h"
#include "Item/NormalGun.h"
#include "const/Const.h"
USING_NS_CC;

class Hero : public Role
{
public:

	static Hero* createHero(cocos2d::Point position);
	void soldierPositionInit(cocos2d::Point position);

	virtual bool init();
	//CREATE_FUNC(Soldier);


	//动作生成
	Animate* createAnimate(const std::string  pActionName);

	//移动精灵
	void move(int face, const std::string pAnimateName);

	bool isKeyPressed(EventKeyboard::KeyCode keyCode);
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);
	void keyPressedDuration(EventKeyboard::KeyCode code);

	void update(float dt = 0.4f);

	//获得当前精灵
	Sprite* getSprite();
	//设置主武器
	void setMainWeapon(Weapon* pWeapon);
	//获取当前主武器
	Weapon* getMainWeapon();

	int m_nowFacing;

	std::map<cocos2d::EventKeyboard::KeyCode, bool> m_keys;

	std::string m_pHeroName = "Hero1";

protected:
	Sprite* m_pHero;

	//主武器
	Weapon* m_pMainWeapon;
};

#endif//!_Hero_H__