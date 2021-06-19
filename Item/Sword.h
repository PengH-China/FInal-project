
/*@file Sword.h
* @author 蔡明宏
* @date 2021/6/1
*/

#ifndef _SWORD_H_
#define _SWORD_H_

#include "Item/Item.h"
#include "Item/Weapon.h"
#include "Item/NormalBullet.h"

class Sword :public Weapon
{
public:
	CREATE_FUNC(Sword);
	/**
	*@brief 创造子弹
	*@author 蔡明宏
	*/
	Bullet* createBullet() override;

	Animate* createAnimate(const std::string  pActionName);

	bool init() override;
};
#endif // !_SWORD_H_
