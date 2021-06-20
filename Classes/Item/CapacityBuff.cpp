#include "CapacityBuff.h"

bool CapacityBuff::init()
{
	auto pCapacityBuff = Sprite::create("Item/Capacity.png");

	if (pCapacityBuff == nullptr) {
		log("pCapacity can't be found");
	}

	bindSprite(pCapacityBuff);
	generatePhysicalBody(QS::message::kTreasureMessage, QS::kCapacityBoxTag);
	return true;
}