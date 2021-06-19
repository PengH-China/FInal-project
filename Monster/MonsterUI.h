
#ifndef _MONSTER_UI_H__
#define _MONSTER_UI_H__

#include "Monster/Monster.h"
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

	Label* m_pHealthMessage;

	Monster* m_pPresentMonster;

	int m_presentHP;
	int m_presentArmor;
	int m_presentAttack;
};
#endif // _MONSTERUI_H__
