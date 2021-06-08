/**
*@file Hero.h
*@author 彭浩(peng hao)
*@time 2021-05-28
*/
#pragma once

#ifndef _Hero_H_
#define _Hero_H_
#include "Role.h"
#include "Const/Const.h"
//#include "Item/Weapon.h"

static float gHeroSpeed = 150.;
static int gHeroDamage = 5;

class Hero :
    public Role
{
public:
    //bool init();

    //move
    void move(int face, const char* pAnimateName,
              int width = 50, int heigh = 100, int frames = 4);

    //stop move
    void stopMove();

    //keep still
    void rest();

    //role die
    void die();

    void dieToStartMenu();

    int getFacing();

    /*Weapon* getMainWeapon();
    void setMainWeapon(Weapon* pNewWeapon);
    void setSecondWeapon(Weapon* pNewWeapon);
    void shiftWeapon();*/

    bool isKeyPressed(EventKeyboard::KeyCode keyCode);
    void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
    void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);
    void keyPressedDuration(EventKeyboard::KeyCode code);

    void roleMoveUpdate(float dt=0.4f);

    /*
    void setSpeed(float speed);

    void clearKeyPress();
    */
    virtual const char* roleName() = 0;
    
protected:

    static Hero* m_pPresentHero;
    //static Item* m_pPresentContactItem;
    /// 武器
    //Weapon* m_pMainWeapon = nullptr;
    //Weapon* m_pSecWeapon = nullptr;

    /// 基本动画
    Animate* m_pRestAnimation = nullptr;
    Animate* m_pMoveAnimation = nullptr;

    //sk::HeroID m_ID;

    bool m_alive = true;
    float m_speed = gHeroSpeed;
    int m_health = 5;
    int m_maxHealth = 5;

    /// 基本属性
    //int m_magicPoint;
    int m_armor = 5;
    int m_maxArmor = 5;
    float m_recoverArmorTime = 0;
    bool m_ifMortal = true;
    int m_baseDamage = gHeroDamage;

    /// 技能属性
    float m_skillCD = 8.f;       // 技能冷却时间
    float m_skillTime = m_skillCD; // 当前技能冷却
    float m_skillLastTime = 1.;        // 技能持续时间
    float m_skillRemainTime = 0;         // 技能剩余时间

    int m_coinNumber = 0;
    std::string m_dieFrame;

    /// 移动状态
    bool m_ifMoved = false;
    bool m_ifStateChanged = false;

    int m_nowFacing = QS::KeyResponse::kRight;    //face direction

    // keyboard detection
    std::map<cocos2d::EventKeyboard::KeyCode, bool> m_keys;
};

#endif//!_CHARACTER_H_