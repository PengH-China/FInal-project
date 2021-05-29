/**
*@file Warrior.cpp
*@author 彭浩(peng hao)
*@time 2021-05-26
*/

#include "Warrior.h"

std::string Warrior::s_roleName = "Warrior";

Warrior::Warrior(){
	grade = 1;
	m_baseDamage = 10;
	m_health = 100;
}

const char* Warrior::roleName() {
	return s_roleName.c_str();
}

void Warrior::upGrade() {
	grade++;//upgrade
	(m_health >= 100) ? NULL : m_health += 10;//increase health value
}