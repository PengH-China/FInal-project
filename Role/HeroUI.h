/**
*@file   
*@author 
*@date   
*/
#ifndef _HERO_UI_H_
#define _HERO_UI_H_

#include "Role/Hero.h"


/**
*@brief 
*@author 
*/
class HeroUI :public Node
{
public:
	CREATE_FUNC(HeroUI);
	/**
	*@brief 生成ui基本组件
	*@author 
	*/
	bool init()override;

	/**
	*@brief 0.1s更新状态
	*@author 
	*/
	void scheduleUI(float dt);

protected:
	Sprite* m_pSprite;
	ProgressTimer* m_pHealth;
	ProgressTimer* m_pArmor;
	ProgressTimer* m_pFirepower;

	Label* m_pHealthMessage;
	Label* m_pArmorMessage;
	Label* m_pFirepowerMessage;
	Label* m_pCoinMessage;
	Label* m_pSpeedMessage;

	Hero* m_pHero;
	int m_presentHP;
	int m_presentArmor;
	int m_presentFirepower;
	int m_presntCoin;
	int m_presentSpeed;
};

#endif // !_HERO_UI_H_

