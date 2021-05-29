/**
*@file Hero.h
*@author 彭浩(peng hao)
*@time 2021-05-28
*/
#pragma once

#ifndef _Hero_H_
#define _Hero_H_
#include "Role.h"
#include "Const.h"
class Hero :
    public Role
{
    //move
    void move();
    void stopMove();
    void rest();

    void die();

    void dieToStartMenu();

    int getFacing();

    void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
    void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);

    bool reduceHealth(int damage = 1);
    void recoverHealth(int healAmount = 1);

    void addArmor(int addAmount);
    bool ifInjured();

    bool costCoins(int coin);
    void gainCoins(int coin);

    int getBaseDamage();
    void raiseDamage(int raiseAmount);

    void setSpeed(float speed);
    void clearKeyPress();

    virtual const char* roleName() = 0;
    
protected:
    int grade;//the grade of warrior

    int m_baseDamage = 150;//the hurt number of character
    int m_health;
    int m_maxHealth;
    int m_speed;//the speed of the character
    int m_maxArmor = 5;

    int m_armor = 5;

    float m_recoverArmorTime = 0;
    bool m_ifMortal = true;
    bool m_alive = true;

    int m_coinNumber;

    int m_nowFacing = JDQS::kRight;

    /// 移动状态
    bool m_ifMoved = false;
    bool m_ifStateChanged = false;

    std::vector<bool>m_isKeyDown = std::vector<bool>(7, false);
    /// 基本动画
    Animate* m_pRestAnimation = nullptr;
    Animate* m_pMoveAnimation = nullptr;
};

#endif//!_CHARACTER_H_