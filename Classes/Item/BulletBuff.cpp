#include "BulletBuff.h"

bool BulletBuff::init()
{
	auto pBulletBuff = Sprite::create("Item/BulletBox.png");
	
	if (pBulletBuff == nullptr) {
		log("pBulletBuff can't be found");
	}

	bindSprite(pBulletBuff);
	generatePhysicalBody(QS::message::kTreasureMessage, QS::kBulletBoxTag);
	return true;
}
