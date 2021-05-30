#pragma once
#ifndef __HOMEPAGE_H__
#define __HOMEPAGE_H__

#include "cocos2d.h"

#include "ui/CocosGUI.h"

using namespace cocos2d::ui;

class HomePage : public cocos2d::Scene
{
public:
    static Scene* createScene();

    virtual bool init();

    void menuItemReturnCallback(Ref* pSender,Widget::TouchEventType type);



    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(HomePage);
};

#endif
