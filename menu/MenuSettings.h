#pragma once
#ifndef __MENUSETTINGS_H__
#define __MENUSETTINGS_H__

#include "cocos2d.h"
#include "AudioEngine.h"

USING_NS_CC;

class MenuSettings : public cocos2d::Scene
{
    bool isEffect = false;
    bool isMusic = false;
public:
    static Scene* createScene();

    virtual bool init();

    //���ر���ͼƬ load background picture
    void loadBackgroundPicture(cocos2d::Ref* pSender);

    //��Ч sound effect
    void menuSoundEffectCallback(cocos2d::Ref* pSender);
    //�������� music
    void menuMusicCallback(cocos2d::Ref* pSender);

    //���ؼ� back to menu
    void menuBackCallback(cocos2d::Ref* pSender);


    // implement the "static create()" method manually
    CREATE_FUNC(MenuSettings);
};

#endif
