#include "Weapon.h"

void Weapon::setDamage(int weaponDamage)
{
	m_weaponDamage = weaponDamage;
}

int Weapon::getDamage()
{
	return m_weaponDamage;
}
bool Weapon::getState()
{
	return m_isInHand;
}
void Weapon::setState(bool isInHand)
{
	//存疑，需要看接口，此方法不一定好
	m_isInHand = isInHand;
	//在被持有的时候不启用模拟，在没被持有则有世界模拟
	m_pSprite->getPhysicsBody()->setEnabled(!isInHand);
}


