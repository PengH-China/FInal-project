#pragma once
/*
* author: peng hao
* 
*/
#ifndef _MONSTER_H_
#define _MONSTER_H_

#include "Role\Role.h"

class Monster :
    public Role
{
    //
public:
    //getPos
    Sprite* getSprite();

    virtual void monsterPositionInit(cocos2d::Point position);

    virtual Animate* createAnimate(const std::string  pActionName) ;

    virtual Monster* createMonster(cocos2d::Point position) ;

    virtual bool init();

protected:

    Sprite* m_pMonsterSprite;
    Animate* m_pMoveAnimation;
};

#endif//!_MONSTER_H_