
/*@file SwordBullet.h
* @author cmh
* @date 2021/6/7
*/
#ifndef _SWORDBULLET_H_
#define _SWORDBULLET_H_
#include "Bullet.h"
class SwordBullet:public Bullet
{
public:
	CREATE_FUNC(SwordBullet);

	virtual void attack(float mouseX, float mouseY, Point heroPoint, int curFacing,
		Node* sprite = nullptr) override;

	virtual bool init() override;
protected:
	Vector<SpriteFrame*> m_rightActionVec;
	Vector<SpriteFrame*> m_leftActionVec;
};

#endif // !_SWORDBULLET_H_


