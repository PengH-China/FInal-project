
/*@file Sword.h
* @author 蔡明宏
* @date 2021/6/1
*/
#pragma once

#ifndef _SWORD_H_
#define _SWORD_H_

#include "Weapon.h"
class Sword :public Weapon
{
public:
	//CREATE_FUNC(Sword);
	/**
	*@brief 创造子弹
	*@author 蔡明宏
	*/
	//Bullet* createBullet() override;

	bool init() override;
};
#endif // !_SWORD_H_
