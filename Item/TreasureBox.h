#pragma once
//author peng hao
#ifndef _TREASURE_BOX_H_
#define _TREASURE_BOX_H_
#include "Item.h"
#include "cocos2d.h"
#include "GlobalPara/GlobalParameter.h"
#include "Const/Const.h"

class TreasureBox :
    public Item
{
public:
    CREATE_FUNC(TreasureBox);

    TreasureBox* createBox();

    bool init()override;

    bool isKeyPressed(EventKeyboard::KeyCode keyCode);
    void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
    void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);

    void update(float dt = 0.4f);
    void openBox();
    void interact();

protected:
    int whichBox;
    Item* m_pBoxItem;
    std::map<cocos2d::EventKeyboard::KeyCode, bool> m_keys;
    bool ableToOpenBox;
};


#endif//!_TREASURE_BOX_H_
