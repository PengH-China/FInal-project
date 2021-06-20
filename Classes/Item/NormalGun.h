/**
*@file NormalGun.h
*@author ²ÌÃ÷ºê
*@date 6/1/2021
*/
#ifndef _NORMALGUN_H_
#define _NORMALGUN_H_

#include "Weapon.h"
#include "NormalBullet.h"
class NormalGun :public Weapon
{
public:
	CREATE_FUNC(NormalGun);
	
	Bullet* createBullet() override;

	bool init() override;
};
#endif // !_NORMALGUN_H_
