
/**
*@file Assassin.cpp
*@author 彭浩(peng hao)
*@time 2021-05-28
*/

#include "Assassin.h"


std::string Assassin::s_roleName = "Assassin";

bool Assassin::init()
{/*
	if (m_pPresentHero == nullptr)
	{
		m_pPresentHero = this;
		scheduleUpdate();
		//setMainWeapon(Gun::create());
		//setSecondWeapon(Spear::create());
		//m_pSecWeapon->setVisible(false);
		//m_pMoveAnimate = creatActorAnimate("Actor/assassin_move", 46, 54);
		//m_pRestAnimate = creatActorAnimate("Actor/assassin_rest", 50, 54);
		//m_pSkillAnimate = creatActorAnimate("Actor/assassin_skill", 52, 56);
		//m_pSkillTempA = m_pMoveAnimate;
		//m_pSkillTempB = m_pRestAnimate;
		m_maxArmor = 3;
		m_armor = 3;
		//m_ID = sk::HeroID::kAssassin;
		return true;
	}
	else
	{
		return false;
	}
	*/
	return true;
}

const char* Assassin::roleName() {
	return s_roleName.c_str();
}

void Assassin::upGrade() {
	grade++;//upgrade
	(m_health >= 100) ? NULL : m_health+=10;//increase health value
}