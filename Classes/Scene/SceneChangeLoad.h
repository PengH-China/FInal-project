#ifndef __SceneChangeLoad_H__
#define __SceneChangeLoad_H__

#include "cocos2d.h"
#include"Scene/Pause.h"
USING_NS_CC;

class SceneChangeLoad :
    public Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();


    static Animate* SceneChangeLoad::createAnimate();


    // implement the "static create()" method manually
    CREATE_FUNC(SceneChangeLoad);
};

#endif // __SceneChangeLoad_H__

//*
