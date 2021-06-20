/**
*@file Hero.cpp
*@author 张子涵(Zhang Zihan),蔡明宏,彭浩
*@time 2021-06-11
*/

//#pragma once
#ifndef _AIHERO_H_
#define _AIHERO_H_
#include "cocos2d.h"
#include "Monster/Monster.h"
#include "Item/MonsterBullet.h"
#include "Item/NormalGun.h"
#include "Const/Const.h"
#include "GlobalPara/GlobalParameter.h"
USING_NS_CC;

class AIHero : public Monster
{
public:

	static AIHero* createAIHero(cocos2d::Point position, std::string pName);
	void soldierPositionInit(cocos2d::Point position);

	virtual bool init(Point position, std::string pName);
	//CREATE_FUNC(Soldier);

	//动作生成
	Animate* createAIAnimate(const std::string  pActionName);

	//移动精灵
	virtual void AImove(int face, const std::string pAnimateName);


	void scheduleUpdateAIHero(float dt);


	Sprite* getSprite();
	//设置主武器
	void setMainWeapon(Weapon* pWeapon);
	//获取当前主武器
	Weapon* getMainWeapon();

	CC_SYNTHESIZE(int, _m_nomFacing, M_nowFacing);
	CC_SYNTHESIZE(int, m_score, Score);
	//背包里的子弹数量
	CC_SYNTHESIZE(int, m_bulletCountInHero,BulletCountInHero);

	bool judgeAIHeroDie();

	void setHeroSpriteName(std::string pName);
	std::string getHeroSpriteName();
protected:


	std::string m_pHeroSpriteName;

	Sprite* m_pHeroSprite;

	clock_t m_lastShotTime;
	

	//主武器
	Weapon* m_pMainWeapon;
};

#endif//!_Hero_H__
