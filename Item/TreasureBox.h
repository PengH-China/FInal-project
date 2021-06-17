//author peng hao
#ifndef _TREASURE_BOX_H_
#define _TREASURE_BOX_H_
#include "Item.h"

class TreasureBox :
    public Item
{
public:
    CREATE_FUNC(TreasureBox);

    bool init()override;
    void update();
    void interact();

protected:
    int whichBox;
    Item* m_pBoxItem;
};


#endif//!_TREASURE_BOX_H_
