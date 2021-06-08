/**
*@file Role.h
*@author 彭浩(peng hao)
*@time 2021-05-26
*/

#pragma once

#ifndef _ROLE_H_
#define _ROLE_H_

#include "cocos2d.h"
#include "Const/Const.h"
USING_NS_CC;

class Role :public cocos2d::Layer
{
public:
	
	/*
	* An Interface that binds a sprite(warrior)
	* author peng hao
	*/
	void bindSprite(Sprite* pSprite);

	/*
	* generate a physics body,and set its nature(性质)
	*/
	bool genePhysicsBody();

	/*
	* return the name of role eg.warrior,assassin and so on
	*/

	static Animate* creatActorUpAnimate(const char* pAnimateName,
										int width = QS::kSoldierWidth,
										int height = QS::kSoldierHeight,
										int frames = 4);
	static Animate* creatActorDownAnimate(const char* pAnimateName,
										int width = QS::kSoldierWidth,
										int height = QS::kSoldierHeight,
										int frames = 4);
	static Animate* creatActorLeftAnimate(const char* pAnimateName,
										int width = QS::kSoldierWidth,
										int height = QS::kSoldierHeight,
										int frames = 4);
	static Animate* creatActorRightAnimate(const char* pAnimateName,
										int width = QS::kSoldierWidth,
										int height = QS::kSoldierHeight,
										int frames = 4);
	virtual const char* roleName() = 0;

	//static Layer* createScene();
protected:
	Sprite* m_pRole;//the character
	
};

#endif//// !_Role_H__
