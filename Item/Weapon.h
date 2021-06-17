/**
*@file Weapon.h
*@author ������
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
	* @brief:���ù�����
	* @author:������
	*/
	void setDamage(int weaponDamage);
	/*
	* @brief:��ȡ������
	* @author:������
	*/
	int getDamage();
	/**
	*@brief �л�����״̬
	*@author ������
	*/
	void setState(bool isInHand);

	/*
	* @brief:ֱ�Ӵӳ�Ա��������ȡ���ڵĳ���״̬
	* @author:������
	*/
	bool getState();
	/**
	*@brief ��������������
	@@author ������
	*/
	/*void interact() override;*/
	//TODO:�������������

	/**
	*@brief �������������ٶ�
	*@author ������
	*/
	void setInterval(float interval);
	/**
	*@brief ��ȡ���������ٶ�
	*@author ������
	*/
	float getInterval();

	/**
	*@brief ��ȡ����һ�η��伸ö�ӵ�
	*@author ������
	*/
	int getBulletCount();
	/**
	*@brief ��������һ�η��伸ö�ӵ�
	*@author ������
	*/
	void setBulletCount(int count);

	/**
	*@brief �����ӵ�
	*@author ������
	*/
	virtual Bullet* createBullet()=0;

	
	Sprite* getWeaponSprite();
protected:
	Sprite* m_pSpriteWeapon = nullptr;
	bool m_isInHand = false;
	int m_weaponDamage;
	float m_attackInterval;
	int m_bulletCount;
};

#endif // !_WEAPON_H_
