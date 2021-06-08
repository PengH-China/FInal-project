/**
*@file Soldier.h
*@author 彭浩(peng hao)
*@time 2021-05-26
*/

#pragma once
#ifndef _SOLDIER_H_
#define _SOLDIER_H_
#include "Role.h"
#include "Hero.h"
#include "cocos2d.h"
USING_NS_CC;

class Soldier :public Hero
{
public:
	//initialization attribute(初始化属性)
	
	bool init() ;

	CREATE_FUNC(Soldier)

	

	const char* roleName();

protected:
	
	static std::string s_roleName;

};

#endif//// !_Soldier_H__