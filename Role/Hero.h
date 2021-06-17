/**
*@file Hero.cpp
*@author ���Ӻ�(Zhang Zihan),������,���(peng hao)
*@time 2021-06-11
*/

//#pragma once
#ifndef _HERO_H_
#define _HERO_H_
#include "cocos2d.h"
#include "Role/Role.h"
#include "Item/NormalGun.h"
#include "Item/Item.h"
#include "Const/Const.h"
USING_NS_CC;

class Hero : public Role
{
public:

	static Hero* createHero(cocos2d::Point position, std::string pName);
	void soldierPositionInit(cocos2d::Point position);

	virtual bool init();
	//CREATE_FUNC(Soldier);


	//��������
	Animate* createAnimate(const std::string  pActionName);

	//�ƶ�����
	virtual void move(int face, const std::string pAnimateName);
	//�����¼�
	bool isKeyPressed(EventKeyboard::KeyCode keyCode);
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);
	void keyPressedDuration(EventKeyboard::KeyCode code);
	
	//ײǽ���
	void setHitWall(bool m_isHitWall);
	bool getIsHitWall();
	//��ת
	float angle(const Vec2& v1, const Vec2& v2);
	void rotate(Vec2& point, float angle);
	void update(float dt = 0.4f);
	////���ý�����Ʒ
	//static void setPresentContactItem(Item* pItem);
	//static Item* getPresentContactItem();

	//��õ�ǰ����
	Sprite* getSprite();
	//����������
	void setMainWeapon(Weapon* pWeapon);
	//��ȡ��ǰ������
	Weapon* getMainWeapon();

	CC_SYNTHESIZE(int, _m_nomFacing, M_nowFacing);

	std::map<cocos2d::EventKeyboard::KeyCode, bool> m_keys;

	void setHeroSpriteName(std::string pName);
	std::string getHeroSpriteName();

	int getCoin()const;
	void setCoin(int coin);
	void addCoin(int coin);
	bool isPickBox();
protected:

	static Item* m_pPresentContactItem ;

	std::string m_pHeroSpriteName = "Hero1";

	Sprite* m_pHeroSprite;

	int m_icoin;
	bool m_isPickBox;
	//Hero* m_pHero;
	//�궨һ���ƶ�
	bool ableToSingleMove = false;
	//�ж��Ƿ�ײǽ
	bool m_isHitWall=false;
	//������
	Weapon* m_pMainWeapon;
};

#endif//!_Hero_H__