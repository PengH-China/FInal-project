/**
*@file Role.h
*@author 彭浩(peng hao)
*@time 2021-05-26
*/

#pragma once

#ifndef _ROLE_H_
#define _ROLE_H_

#include "cocos2d.h"
USING_NS_CC;

class Role :public cocos2d::Node
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
	virtual const char* roleName() = 0;
protected:
	Sprite* m_role;//the character
	
};

#endif//// !_Role_H__
