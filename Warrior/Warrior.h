/**
*@file Warrior.h
*@author 彭浩(peng hao)
*@time 2021-05-26
*/

#pragma once
#ifndef _WARRIOR_H_
#define _WARRIOR_H_
#include "Role.h"
#include "Hero.h"
#include "cocos2d.h"
USING_NS_CC;

class Warrior :public Hero
{
public:
	//initialization attribute(初始化属性)
	static cocos2d::Scene* createScene();
	bool init() override;

	CREATE_FUNC(Warrior)

	int  damageNum(){ return m_baseDamage * grade; }
	//upgrade
	void upGrade();

	const char* roleName();

	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* events) ;
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* events) ;

	bool isKeyPressed(EventKeyboard::KeyCode keyCode);


	void update(float delta)override;
	// Register an update function that checks to see if the CTRL key is pressed
	// and if it is displays how long, otherwise tell the user to press it
	void keyPressedDuration(EventKeyboard::KeyCode code);
protected:
	
	std::map<cocos2d::EventKeyboard::KeyCode, bool> keys;
	static std::string s_roleName;
};

#endif//// !_Warrior_H__