/**
*@file NormalGun.h
*@author 蔡明宏
*@date 6/1/2021
*/
#pragma once

#ifndef _NORMALGUN_H_
#define _NORMALGUN_H_

#include "Weapon.h"
#include "NormalBullet.h"
class NormalGun :public Weapon
{
public:
	CREATE_FUNC(NormalGun);
	/**
	*@brief 创造子弹
	*@author 蔡明宏
	*/
	Bullet* createBullet() override;

	bool init() override;
};
#endif // !_NORMALGUN_H_
