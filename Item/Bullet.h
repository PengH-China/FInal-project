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


	CC_SYNTHESIZE(float, m_speed, BulletSpeed);
	CC_SYNTHESIZE(int, m_damage, Damage);
	
	/**
	*@brief 绑定精灵图像
	*@author 蔡明宏
	*/
	void bindSprite(Sprite* kSprite, QS::Kind kind,
		QS::BulletShape shape, std::string name = QS::Name::kBullet);

	
protected:
	Sprite* m_pBulletSprite;

	bool m_isArrive;

	QS::Kind m_kind;

	void moveEnd();
};

#endif 


