
#ifndef _SHOTGUN_H_
#define _SHOTGUN_H_

#include "Weapon.h"
#include "ShotGunBullet.h"
class ShotGun :public Weapon
{
public:
	CREATE_FUNC(ShotGun);

	Bullet* createBullet() override;

	bool init() override;

};

#endif // !_SHOTGUN_H_
