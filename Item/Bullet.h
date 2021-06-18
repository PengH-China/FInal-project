/**
*@file Bullet.h
*@author ������
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
	*@brief �ӵ���Ŀ���������
	*@brief ���麯��
	*@author ������
	*/
	virtual void attack(float direX, float direY, Point heroPoint, int curFacing,
		Node* sprite = nullptr) = 0;
	/**
	*@brief ��ȡ�ӵ��ٶ�
	*@author ������
	*/

	float getSpeed();

	/**
	*@brief �����ӵ��ٶ�
	*@author ������
	*/
	void setSpeed(float speed);

	/**
	*@brief �󶨾���ͼ��
	*@author ������
	*/
	void bindSprite(Sprite* kSprite, QS::Kind kind,
		QS::BulletShape shape, std::string name = QS::Name::kBullet);

	/**
	*@brief �����˺�
	*@author ������
	*/
	void setDamage(int damage);

	/**
	*@brief ��ȡ�˺�
	*@author ������
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


