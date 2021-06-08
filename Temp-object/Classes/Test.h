#pragma once
#include "cocos2d.h"
USING_NS_CC;
class Test :
    public Scene
{
public:
    static cocos2d::Scene* createScene();

    bool init();

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

    static EventListenerKeyboard* keyBoardListenerOne;
    void addPlayer();
   
   

    CREATE_FUNC(Test);
};

