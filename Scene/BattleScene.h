/**
*@file BattleScene.h
*@author ÕÅ×Óº­
*@date 6/1/2021
*/


#pragma once
#ifndef __BATTLESCENE_H__
#define __BATTLESCENE_H__

#include "cocos2d.h"

using namespace cocos2d;

class BattleScene : public cocos2d::Scene
{

public:
    static Scene* createScene();

    virtual bool init();

    //load bakground picture
    void loadBackgroundMap(cocos2d::Ref* pSender);
    //init m_map and m_map
    void BattleScene::setTiledMap(TMXTiledMap* map);
    
    //back to menu
    void menuBackCallback(cocos2d::Ref* pSender);
    //set each gid a tag name
    void setGidTag();
    // implement the "static create()" method manually
    CREATE_FUNC(BattleScene);
protected:
    TMXTiledMap* m_map;
    TMXLayer* m_meta;
};

#endif
