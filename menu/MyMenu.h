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

    //three buttons
    void menuItem1Callback(cocos2d::Ref* pSender);//start
    void menuItem2Callback(cocos2d::Ref* pSender);//settings
    void menuItem3Callback(cocos2d::Ref* pSender);//help


    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(MyMenu);
};

#endif
