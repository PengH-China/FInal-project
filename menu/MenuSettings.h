#pragma once
#ifndef __MENUSETTINGS_H__
#define __MENUSETTINGS_H__

#include "cocos2d.h"

USING_NS_CC;

class MenuSettings : public cocos2d::Scene
{
public:
    static Scene* createScene();

    virtual bool init();


    void menuItem1Callback(cocos2d::Ref* pSender);
    void menuItem2Callback(cocos2d::Ref* pSender);

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(MenuSettings);
};

#endif
