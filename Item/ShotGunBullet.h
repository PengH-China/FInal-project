
#ifndef _SHOTGUNBULLET_H_
#define _SHOTGUNBULLET_H_

#include "Bullet.h"
#include "Role/Hero.h"
class ShotGunBullet :public Bullet
{
public:
	CREATE_FUNC(ShotGunBullet);

	virtual void attack(float direX, float direY, Point heroPoint, int curFacing,
		Node* sprite = nullptr) override;

	virtual bool init() override;

};
#endif
