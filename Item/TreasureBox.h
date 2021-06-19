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

    
    void openBox();
    void interact();

protected:
    int whichBox;
    Item* m_pBoxItem;
};


#endif//!_TREASURE_BOX_H_
