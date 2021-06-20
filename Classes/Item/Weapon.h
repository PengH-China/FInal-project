
#ifndef _WEAPON_H_
#define _WEAPON_H_

#include "Bullet.h"
#include "AudioEngine.h"
#include "Item/Item.h" 

using namespace cocos2d;
class Weapon :public Item
{
public:
	CC_SYNTHESIZE(int, m_damage, Damage);
	CC_SYNTHESIZE(bool, m_state, State);
	CC_SYNTHESIZE(int, m_interval, Interval);
	//武器现有子弹数量
	CC_SYNTHESIZE(int, m_bulletCount, BulletCount);
	//武器最大子弹载量
	CC_SYNTHESIZE(int, m_bulletCountMax, BulletCountMax);
	CC_SYNTHESIZE(std::string, m_weaponName, WeaponName);

	virtual Bullet* createBullet();

	bool isKeyPressed(EventKeyboard::KeyCode keyCode);
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);

	//换枪
	void interact();
	void update(float dt=0.4f);
	Sprite* getWeaponSprite();
protected:
	Sprite* m_pSpriteWeapon = nullptr;
	std::map<cocos2d::EventKeyboard::KeyCode, bool> m_keys;
};

#endif // !_WEAPON_H_
