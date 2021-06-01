/**
*@file Weapon.h
*@author 蔡明宏
*@date 5/28/2021
*/
#ifndef _WEAPON_H_
#define _WEAPON_H_

#include "Bullet.h"
#include "AudioEngine.h"
#include "Item.h" 

using namespace cocos2d;
class Weapon :public Item
{
public:
	/*
	* @brief:设置攻击力
	* @author:蔡明宏
	*/
	void setDamage(int weaponDamage);
	/*
	* @brief:获取攻击力
	* @author:蔡明宏
	*/
	int getDamage();
	/**
	*@brief 切换持有状态
	*@author 蔡明宏
	*/
	void setState(bool isInHand);

	/*
	* @brief:直接从成员变量处获取现在的持有状态
	* @author:蔡明宏
	*/
	bool getState();
	/**
	*@brief 与手中武器交换
	@@author 蔡明宏
	*/
	void interact() override;
	//TODO:与地面武器交换

protected:
	Sprite* m_pSpriteWeapon = nullptr;

	bool m_isInHand = false;
	int m_weaponDamage;
};


#endif // !_WEAPON_H_
