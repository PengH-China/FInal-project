#ifndef __MONSTER_H__
#define __MONSTER_H__
#include "Monster.h"
#include "Item/MonsterBullet.h"
//author peng hao
class MonsterFly :
    public Monster
{
public:
    CREATE_FUNC(MonsterFly);

	void update(float dt ) override;

    bool init() override;

    MoveBy* createRandAction();
    static MonsterFly* createMonster(cocos2d::Point position);

    static Animate* createAnimate(const std::string  pActionName = m_StrMonsterAnmi);

    void move();

    //设置主武器
    //void setMainWeapon(Weapon* pWeapon);
    //获取当前主武器
    //Weapon* getMainWeapon();
private:
    static const std::string m_StrMonsterAnmi;
    static const std::string m_StrMonsterName;
    //主武器
    //Weapon* m_pMainWeapon;
    clock_t m_lastShotTime;
};






#endif
