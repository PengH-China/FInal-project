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
#include "Monster/Monster.h"
#include "cocos2d.h"
#include "Role/Hero.h"
#include "Monster/MonsterGroup.h"
#include "GlobalPara/GlobalParameter.h"
#include "Role/HeroUI.h"
#include"Monster/Monster.h"
#include"Scene/SceneChangeLoad.h"
#include"Scene/MapLayer.h"
#include "Scene/Pause.h"
#include"Scene/GameOver.h"

using namespace cocos2d;

class BattleScene : public cocos2d::Scene
{

public:
    //BattleScene(TMXTiledMap* map) : m_pMap(map) { };
    //BattleScene* createWithPhysics();
    //static BattleScene* create(TMXTiledMap* map);

   // static Scene* createScene(TMXTiledMap* map);

    virtual bool init();

    //void onEnter();
    void scheduleUpdateHeroDie(float dt);

    static cocos2d::Scene* createScene();

    static BattleScene* createWithPhysics();

    void menuPauseCallback(cocos2d::Ref* pSender);

    void addUI();
protected:
    TMXTiledMap* m_pMap = nullptr;
    TMXLayer* m_pMeta = nullptr;
    clock_t m_lastShotTime;
    float mapHeight, mapWidth;
    float tileHeight, tileWidth;
    //static EventListenerKeyboard* keyBoardListenerOne;
};

#endif
