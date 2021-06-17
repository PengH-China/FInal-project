/*
* @file NormalBullet.h
* @author:²ÌÃ÷ºê
* @time:2021/5/29
*/

#ifndef _NORMALBULLET_H_
#define _NORMALBULLET_H_

#include "Bullet.h"
#include "Role/Hero.h"
class NormalBullet :public Bullet
{
public:
	CREATE_FUNC(NormalBullet);

	virtual void attack(float direX, float direY, Point heroPoint, int curFacing,
		Node* sprite = nullptr) override;

	virtual bool init() override;

};
#endif // !_NORMALBULLET_H_

