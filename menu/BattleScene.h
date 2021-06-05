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
    void loadBackgroundPicture(cocos2d::Ref* pSender);


    //back to menu
    void menuBackCallback(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(BattleScene);
};

#endif
