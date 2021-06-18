/**
*@file BattleScene.h
*@author 张子涵 方新宇
*@date 6/5/2021
*/


#pragma once
#ifndef __BATTLESCENE_H__
#define __BATTLESCENE_H__

#include "cocos2d.h"
#include "Const/Const.h"
//#include "Role/HeroUI.h"
#include "Monster/MonsterGroup.h"
//#include "Item/TreasureBox.h"
using namespace cocos2d;

class BattleScene : public cocos2d::Layer
{

public:
    BattleScene(TMXTiledMap* map) : m_pMap(map) { };
    //BattleScene* createWithPhysics();
    static BattleScene* create(TMXTiledMap* map);

    static Scene* createScene(TMXTiledMap* map);

    virtual bool init();

    void onEnter();

    void addEdge();

    //load bakground picture
    void loadBackgroundMap(cocos2d::Ref* pSender);
    //init m_map and m_map
    void BattleScene::setTiledMap(TMXTiledMap* map);
    //back to menu
    void menuBackCallback(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
    void addPlayerAndUI();
    bool addMonster();
    Monster* createMonsterRand();
    void createBarrier();
    void addBox();

    bool onContactBegin(PhysicsContact& contact);
    bool onContactSeparate(PhysicsContact& contact);

    //鼠标事件
    bool onMouseDown(EventMouse* event);
    void onMouseUp(EventMouse* event);
    void onMouseMove(EventMouse* event);
    //CREATE_FUNC(BattleScene);
protected:
    TMXTiledMap* m_pMap = nullptr;
    TMXLayer* m_pMeta = nullptr;
    clock_t m_lastShotTime;
    //static EventListenerKeyboard* keyBoardListenerOne;
};

#endif
