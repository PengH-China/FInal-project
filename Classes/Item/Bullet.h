
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
	*/
	virtual void attack(float direX, float direY, Point heroPoint, int curFacing,
		Node* sprite = nullptr) = 0;


	CC_SYNTHESIZE(float, m_speed, BulletSpeed);
	CC_SYNTHESIZE(int, m_damage, Damage);
	
	/**
	*@brief 绑定精灵图像
	*/
	void bindSprite(Sprite* kSprite, QS::Kind kind,
		QS::BulletShape shape, std::string name = QS::Name::kBullet);

	
protected:
	Sprite* m_pBulletSprite;


	QS::Kind m_kind;

};

#endif 


