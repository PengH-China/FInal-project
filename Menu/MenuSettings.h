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

    //º”‘ÿ±≥æ∞Õº∆¨ load background picture
    void loadBackgroundPicture(cocos2d::Ref* pSender);

    //“Ù–ß sound effect
    void menuSoundEffectCallback(cocos2d::Ref* pSender);
    //±≥æ∞“Ù¿÷ music
    void menuMusicCallback(cocos2d::Ref* pSender);

    //∑µªÿº¸ back to menu
    void menuBackCallback(cocos2d::Ref* pSender);


    // implement the "static create()" method manually
    CREATE_FUNC(MenuSettings);
};

#endif
