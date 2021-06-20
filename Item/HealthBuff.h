
#ifndef _HEALTHBUFF_H_
#define _HEALTHBUFF_H_

#include "Item.h"

class HealthBuff :public Item
{
public:
	CREATE_FUNC(HealthBuff);

	virtual bool init() override;

};
#endif