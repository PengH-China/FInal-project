
/**
*@file Assassin.cpp
*@author 彭浩(peng hao)
*@time 2021-05-28
*/

#include "Assassin.h"


std::string Assassin::s_roleName = "Assassin";

Assassin::Assassin() {
	grade  = 1;
	m_baseDamage = 10;
	m_health = 100;
}

const char* Assassin::roleName() {
	return s_roleName.c_str();
}

void Assassin::upGrade() {
	grade++;//upgrade
	(m_health >= 100) ? NULL : m_health+=10;//increase health value
}