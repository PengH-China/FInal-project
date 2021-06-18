/**
*@file Bullet.h
*@author 蔡明宏
*@date 5/26/2021
*/

#pragma once
#ifndef _BULLET_H_
#define _BULLET_H_

#include "cocos2d.h"
#include "Const/Const.h"
using namespace cocos2d;

class Bullet :public Node {
public:
	/**
	*@brief 子弹对目标产生攻击
	*@brief 纯虚函数
	*@author 蔡明宏
	*/
	virtual void attack(float direX, float direY, Point heroPoint, int curFacing,
		Node* sprite = nullptr) = 0;
	/**
	*@brief 获取子弹速度
	*@author 蔡明宏
	*/

	float getSpeed();

	/**
	*@brief 设置子弹速度
	*@author 蔡明宏
	*/
	void setSpeed(float speed);

	/**
	*@brief 绑定精灵图像
	*@author 蔡明宏
	*/
	void bindSprite(Sprite* kSprite, QS::Kind kind,
		QS::BulletShape shape, std::string name = QS::Name::kBullet);

	/**
	*@brief 设置伤害
	*@author 蔡明宏
	*/
	void setDamage(int damage);

	/**
	*@brief 获取伤害
	*@author 蔡明宏
	*/
	int getDamage();
protected:
	Sprite* m_pBulletSprite;
	float m_bulletSpeed;
	bool m_isArrive;
	int m_damage;
	QS::Kind m_kind;

	void moveEnd();
};

#endif 


