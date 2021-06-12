#ifndef __SceneChangeLoad_H__
#define __SceneChangeLoad_H__

#include "cocos2d.h"

USING_NS_CC;

class SceneChangeLoad :
    public Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

    Animate* SceneChangeLoad::createAnimate();

    // implement the "static create()" method manually
    CREATE_FUNC(SceneChangeLoad);
};

#endif // __HELLOWORLD_SCENE_H__

//*
