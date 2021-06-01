/**
*@file Gun.h
*@author 蔡明宏
*@date 6/1/2021
*/

#ifndef _GUN_H_
#define _GUN_H_

#include "Weapon.h"
class Gun :public Weapon
{
public:
	/**
	*@brief 创造一枚子弹
	*@author 蔡明宏
	*/
	virtual Bullet* createBullet();

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
	*@brief 设置武器发射速度
	*@author 蔡明宏
	*/
	void setInterval(float interval);

	/**
	*@brief 设置武器一次发射几枚子弹
	*@author 蔡明宏
	*/
	void setBulletCount(int count);
protected:
	float m_attackInterval;
	int m_bulletCount;
};
#endif // !_SWORD_H_
