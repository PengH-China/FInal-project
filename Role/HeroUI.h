/**
*@file
*@author
*@date
*/
#ifndef _HERO_UI_H_
#define _HERO_UI_H_

#include "Role/Hero.h"
#include "GlobalPara/GlobalParameter.h"

/**
*@brief
*@author
*/
class HeroUI :public Node
{

public:
	CREATE_FUNC(HeroUI);

	bool init()override;

	void scheduleUpdateUI(float dt);

protected:
	ProgressTimer* m_pHealth;
	ProgressTimer* m_pArmor;
	ProgressTimer* m_pFirepower;

	Sprite* m_pBoard;
	Label* m_pCoinMessage;
	Label* m_pSpeedMessage;
	Label* m_pScoreMessage;
	Label* m_pHealthMessage;
	Label* m_pArmorMessage;
	Label* m_pAttackMessage;

	Hero* m_pPresentHero;
	int m_presentHP;
	int m_presentArmor;
	int m_presentAttack;
	int m_presentCoin;
	int m_presentSpeed;
	int m_presentScore;
};

#endif // !_HERO_UI_H_

