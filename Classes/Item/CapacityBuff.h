#ifndef _CAPACITYBUFF_H_
#define _CAPACITYBUFF_H_

#include "Item.h"

class CapacityBuff :public Item
{
public:
	CREATE_FUNC(CapacityBuff);

	virtual bool init() override;

};
#endif