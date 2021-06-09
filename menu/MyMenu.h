#pragma once
#ifndef __MY_MENU_H__
#define __MY_MENU_H__

#include "cocos2d.h"

USING_NS_CC;

class MyMenu: public cocos2d::Scene
{
public:
    static Scene* createScene();

    virtual bool init();

    void loadBackgroundPicture(cocos2d::Ref* pSender);

    //four buttons
    void menuStartCallback(cocos2d::Ref* pSender);//start
    void menuJoinGameCallback(cocos2d::Ref* pSender);//join
    void menuSettingsCallback(cocos2d::Ref* pSender);//settings
    void menuHelpCallback(cocos2d::Ref* pSender);//help


    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(MyMenu);
};

#endif
