
/*@file Sword.h
* @author ������
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
	*@brief �����ӵ�
	*@author ������
	*/
	//Bullet* createBullet() override;

	bool init() override;
};
#endif // !_SWORD_H_
