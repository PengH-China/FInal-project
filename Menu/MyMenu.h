#pragma once
#ifndef __MY_MENU_H__
#define __MY_MENU_H__

#include "Scene/HomePage.h"
#include "MenuSettings.h"
#include "MenuHelp.h"
#include "cocos2d.h"
#include"Scene/SceneChangeLoad.h"

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
    void menuExitCallback(cocos2d::Ref* pSender);//exit


    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(MyMenu);
};

#endif
