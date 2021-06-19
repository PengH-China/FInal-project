#pragma once
#ifndef __HOMEPAGE_H__
#define __HOMEPAGE_H__

#include "cocos2d.h"
#include "GlobalPara/GlobalParameter.h"
#include"SceneChangeLoad.h"
#include "BattleScene.h"

#include <vector>

using namespace cocos2d;

class HomePage : public cocos2d::Scene
{
    //角色的数量 the num of actors
    const int ACTOR_NUM = 2;

    //角色的地址 the address of actors
    const std::string actorImagePath[2]
        = { "actor/Soldier-1.png",
        "actor/Soldier-2.png"};

    int num[10] = {};

public:
    static Scene* createScene();

    virtual bool init();

    //load bakground picture
    void loadBackgroundPicture(cocos2d::Ref* pSender);


    void selectPlayerOrAICallback(Ref* pSender,const int i);

    void leftArrowCallback(Ref* pSender,const int i);
    void rightArrowCallback(Ref* pSender, const int i);

    //start game
    void startGameCallback(cocos2d::Ref* pSender);
    //back to menu
    void menuBackCallback(cocos2d::Ref* pSender);



    // implement the "static create()" method manually
    CREATE_FUNC(HomePage);
};

#endif
