
#ifndef _BULLETBUFF_H_
#define _BULLETBUFF_H_

#include "Item.h"

class BulletBuff :public Item
{
public:
	CREATE_FUNC(BulletBuff);

	virtual bool init() override;
};


#endif // !_BULLETBUFF_H_



