/**
*@file BattleScene.h
*@author 张子涵 方新宇
*@date 6/5/2021
*/


#pragma once
#ifndef __BATTLESCENE_H__
#define __BATTLESCENE_H__

#include "cocos2d.h"

using namespace cocos2d;

class BattleScene : public cocos2d::Scene
{

public:

    BattleScene(TMXTiledMap* map) : m_pMap(map) { };

	static Scene* createScene(TMXTiledMap* map);

	static BattleScene* create(TMXTiledMap* map);

    //BattleScene(TMXTiledMap* map) : m_pMap(map) { };
    //BattleScene* createWithPhysics();
    //static BattleScene* create();
    //static Scene* createScene();

    virtual bool init() override;

    //load bakground picture
    void loadBackgroundMap(cocos2d::Ref* pSender);
    //init m_map and m_map
    void BattleScene::setTiledMap(TMXTiledMap* map);
    //back to menu
    void menuBackCallback(cocos2d::Ref* pSender);
    //set each gid a tag name
    void setGidTag();
    // implement the "static create()" method manually
    void addPlayer(/*float dt*/);

    void createBarrier();
    //CREATE_FUNC(BattleScene);
    bool BattleScene::onContactBegin(PhysicsContact& contact);
protected:
    TMXTiledMap* m_pMap=nullptr;
    TMXLayer* m_pMeta=nullptr;
    //static EventListenerKeyboard* keyBoardListenerOne;
};

#endif
