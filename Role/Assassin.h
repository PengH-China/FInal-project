
/**
*@file Assassin.h
*@author 彭浩(peng hao)
*@time 2021-05-26
*/

#pragma once
#ifndef _ASSASSIN_H_
#define _ASSASSIN_H_
#include "Role.h"
#include "cocos2d.h"
#include "Hero.h"
USING_NS_CC;

class Assassin :public Hero
{
public:
	//initialization attribute(初始化属性)
	CREATE_FUNC(Assassin);

		
	bool init() override;
	
	//float skill() override;

	//void skillEnd() override;
	int  damageNum() { return m_baseDamage * grade; }
	//upgrade
	void upGrade() ;

	const char* roleName();


protected:
	Animate* m_pSkillAnimate = nullptr;
	Animate* m_pSkillTempA = nullptr;
	Animate* m_pSkillTempB = nullptr;

	float m_speedUP = 1.5;

	static std::string s_roleName;
};

#endif//// !_Warrior_H__