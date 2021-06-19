
#ifndef _ROLE_H_
#define _ROLE_H_

#include "cocos2d.h"
#include "Const/Const.h"
USING_NS_CC;

class Role :public cocos2d::Layer
{
public:
	
	/*
	* An Interface that binds a sprite(warrior)
	* author peng hao
	*/
	void bindSprite(Sprite* pSprite);

	/*
	* generate a physics body,and set its nature(性质)
	*/
	virtual bool genePhysicsBody();

	
	CC_SYNTHESIZE(int, m_health, Health);
	CC_SYNTHESIZE(int, m_maxHealth, MaxHealth);
	CC_SYNTHESIZE(int, m_armor, Armor);
	CC_SYNTHESIZE(int, m_maxArmor, MaxArmor);
	CC_SYNTHESIZE(int, m_firePower, FirePower);
	CC_SYNTHESIZE(int, m_maxFirePower, MaxFirePower);

	//static Layer* createScene();
protected:
	Sprite* m_sprite;//the character
	
};

#endif//// !_Role_H__
