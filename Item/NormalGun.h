/**
*@file NormalGun.h
*@author ������
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
	*@brief �����ӵ�
	*@author ������
	*/
	Bullet* createBullet() override;

	bool init() override;
};
#endif // !_NORMALGUN_H_
