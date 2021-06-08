#pragma once

#ifndef _START_SCENE_H_
#define _START_SCENE_H_

#include "cocos2d.h"
USING_NS_CC;
class StartScene :public Scene
{
protected:

    Sprite* m_pRole;

    std::map<cocos2d::EventKeyboard::KeyCode, bool> keys;

public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(StartScene);

    void addMonster(float dt);

    bool onTouchBegan(Touch* touch, Event* unused_event);

    bool onContactBegin(PhysicsContact& contact);

    //void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* events);

    void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* events);
    void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* events);

    bool isKeyPressed(EventKeyboard::KeyCode keyCode);


    void update(float delta)override;
        // Register an update function that checks to see if the CTRL key is pressed
        // and if it is displays how long, otherwise tell the user to press it

    void keyPressedDuration(EventKeyboard::KeyCode code);
};
#endif // !1



