#include "HealthBuff.h"

bool HealthBuff::init()
{
	auto pHelthBuff = Sprite::create("Item/HealthBox.png");

	if (pHelthBuff == nullptr) {
		log("pHelthBuff can't be found");
	}

	bindSprite(pHelthBuff);
	generatePhysicalBody(QS::message::kTreasureMessage, QS::kHealthBoxTag);
	return true;
}


