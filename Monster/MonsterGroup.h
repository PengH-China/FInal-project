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

    void update(float dt) override;

    bool init() override;

    static MonsterFly* createMonster(cocos2d::Point position);

    static Animate* createAnimate(const std::string  pActionName = m_StrMonsterAnmi);

private:
    static const std::string m_StrMonsterAnmi;
    static const std::string m_StrMonsterName;
    //Ö÷ÎäÆ÷
    //Weapon* m_pMainWeapon;
    clock_t m_lastShotTime;
};

class MonsterBlueOne :
    public Monster
{
public:
    CREATE_FUNC(MonsterBlueOne);

    void update(float dt) override;

    bool init() override;

    static MonsterBlueOne* createMonster(cocos2d::Point position);

    static Animate* createAnimate(const std::string  pActionName = m_StrMonsterAnmi);

private:
    static const std::string m_StrMonsterAnmi;
    static const std::string m_StrMonsterName;
    //Ö÷ÎäÆ÷
    //Weapon* m_pMainWeapon;
    clock_t m_lastShotTime;
};

class MonsterCrawl :
    public Monster
{
public:
    CREATE_FUNC(MonsterCrawl);

    void update(float dt) override;

    bool init() override;

    static MonsterCrawl* createMonster(cocos2d::Point position);

    static Animate* createAnimate(const std::string  pActionName = m_StrMonsterAnmi);

private:
    static const std::string m_StrMonsterAnmi;
    static const std::string m_StrMonsterName;
    //Ö÷ÎäÆ÷
    //Weapon* m_pMainWeapon;
    clock_t m_lastShotTime;
};

class MonsterBlueTwo :
    public Monster
{
public:
    CREATE_FUNC(MonsterBlueTwo);

    void update(float dt) override;

    bool init() override;

    static MonsterBlueTwo* createMonster(cocos2d::Point position);

    static Animate* createAnimate(const std::string  pActionName = m_StrMonsterAnmi);

private:
    static const std::string m_StrMonsterAnmi;
    static const std::string m_StrMonsterName;
    //Ö÷ÎäÆ÷
    //Weapon* m_pMainWeapon;
    clock_t m_lastShotTime;
};

#endif