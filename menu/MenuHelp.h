#pragma once
#ifndef __MENUHELP_H__
#define __MENUHELP_H__

#include "cocos2d.h"

USING_NS_CC;

class MenuHelp : public cocos2d::Scene
{
public:
    static Scene* createScene();

    virtual bool init();

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(MenuHelp);
};

#endif
