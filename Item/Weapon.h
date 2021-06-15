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
	/*void interact() override;*/
	//TODO:与地面武器交换

	/**
	*@brief 设置武器发射速度
	*@author 蔡明宏
	*/
	void setInterval(float interval);
	/**
	*@brief 获取武器发射速度
	*@author 蔡明宏
	*/
	float getInterval();

	/**
	*@brief 获取武器一次发射几枚子弹
	*@author 蔡明宏
	*/
	int getBulletCount();
	/**
	*@brief 设置武器一次发射几枚子弹
	*@author 蔡明宏
	*/
	void setBulletCount(int count);

	/**
	*@brief 创造子弹
	*@author 蔡明宏
	*/
	virtual Bullet* createBullet();

	
	Sprite* getWeaponSprite();
protected:
	Sprite* m_pSpriteWeapon = nullptr;
	bool m_isInHand = false;
	int m_weaponDamage;
	float m_attackInterval;
	int m_bulletCount;
};

#endif // !_WEAPON_H_
