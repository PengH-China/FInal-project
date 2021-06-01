#include "Gun.h"

float Gun::getInterval()
{
	return m_attackInterval;
}
int Gun::getBulletCount()
{
	return m_bulletCount;
}
void Gun::setInterval(float interval)
{
	m_attackInterval = interval;
}
void Gun::setBulletCount(int count)
{
	m_bulletCount = count;
}
Bullet* Gun::createBullet()
{
	return nullptr;
}