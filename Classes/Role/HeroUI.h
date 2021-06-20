
#ifndef _HERO_UI_H_
#define _HERO_UI_H_

#include "Role/Hero.h"
#include "GlobalPara/GlobalParameter.h"


class HeroUI :public Node
{

public:
	CREATE_FUNC(HeroUI);

	bool init()override;

	void scheduleUpdateUI(float dt);

protected:
	ProgressTimer* m_pHealth;
	ProgressTimer* m_pArmor;
	ProgressTimer* m_pWeaponBullet;

	Sprite* m_pBoard;
	Label* m_pBulletHeroMessage;
	Label* m_pTimeMessage;
	Label* m_pScoreMessage;
	Label* m_pHealthMessage;
	Label* m_pArmorMessage;
	Label* m_pBulletWeaponMessage;

	Hero* m_pPresentHero;
	int m_presentHP;
	int m_presentArmor;
	int m_presentBulletWeapon;
	int m_presentBulletHero;
	int m_presentTime;
	int m_presentScore;
};

#endif // !_HERO_UI_H_

