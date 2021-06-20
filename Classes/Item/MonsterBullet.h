

#ifndef _MONSTERBULLET_H
#define _MONSTERBULLET_H

#include "Item/Bullet.h"
#include "Monster/Monster.h"

class MonsterBullet :public Bullet
{
public:
	CREATE_FUNC(MonsterBullet);

	virtual void attack(float direX, float direY, Point heroPoint, int curFacing,
		Node* sprite = nullptr) override;

	virtual bool init() override;

};
#endif // !_MONSTERBULLET_H
